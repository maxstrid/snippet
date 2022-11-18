#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>

#include "toml.h"

namespace toml {
enum TomlConfigType {
  SNIPPETS,
  SNIPPET_GROUPS,
};

Config read(const std::string filename) {
  Config config_map;

  config_map.snippet_groups = std::nullopt;

  if (std::filesystem::path(filename).extension() != ".toml") {
    std::cerr << filename << ": file not toml\n";
    std::exit(1);
  }

  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open()) {
    std::perror(filename.c_str());
    std::exit(1);
  }
  std::map<std::string, std::string> snippet_map;
  std::map<std::string, std::vector<std::string>> group_map;
  std::vector<std::string> group_vec;
  std::string og_key;
  std::string file_str;
  std::string split;
  std::string group_val;
  TomlConfigType config_type;
  int count = 0;

  while (std::getline(file, file_str)) {
    if (file_str[0] == '[') {
      std::string toml_conf_header = file_str.substr(1, file_str.size() - 2);

      if (toml_conf_header == "snippets") {
        config_type = TomlConfigType::SNIPPETS;
      } else {
        config_type = TomlConfigType::SNIPPET_GROUPS;
      }
    }

    if (file_str[0] == '#' || file_str.empty() || file_str[0] == '[') {
      continue;
    }

    std::stringstream file_stream(file_str);
    std::string key, value;

    count = 0;
    while (std::getline(file_stream, split, '=')) {
      if (count) {
        value = split;
      } else {
        key = split;
      }
      count++;
    }

    // Remove inline comments from value
    std::stringstream value_stream(value);
    std::getline(value_stream, split, '#');

    value = split;
    // Remove whitespace
    key.erase(std::remove_if(key.begin(), key.end(), isspace), key.end());
    value.erase(std::remove_if(value.begin(), value.end(), isspace),
                value.end());
    
    if (config_type == SNIPPET_GROUPS) {
        if (value.find('[') != std::string::npos) {
          og_key = key;
        }

        if (value.empty()) {
          group_val = key;
        } else {
          group_val = value;
        }
        if (group_val.find(']') == std::string::npos) {
            group_vec.push_back(group_val);
        } else {
          group_vec.push_back(group_val);
          std::pair<std::string, std::vector<std::string>> pr(og_key, group_vec);
          group_map.insert(pr);
          group_vec.clear();
        }
    } else {
      std::pair<std::string, std::string> pr(key, value);
      snippet_map.insert(pr);
    }
  }

  // Needed because std::optional doesn't like me
  config_map.snippets = snippet_map;
  config_map.snippet_groups = group_map;

  return config_map;
}
} // namespace toml