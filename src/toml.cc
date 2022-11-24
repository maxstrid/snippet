#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>

#include "toml.h"

enum TomlConfigType {
  SNIPPETS,
  SNIPPET_GROUPS,
};

Config::Config(const std::string filepath) {
  if (std::filesystem::path(filepath).extension() != ".toml") {
    std::cerr << filename << ": file not toml\n";
    std::exit(1);
  }

  std::ifstream file(filepath, std::ios::binary);

  if (!file.is_open()) {
    std::perror(filename.c_str());
    std::exit(1);
  } else {
    filename = filepath;
  }

  std::string split;
  std::string key, prev_key, value;

  // Because of how optionals work I need to set
  // the optional to this rather than accessing the optional
  std::map<std::string, std::string> snippet_map;
  std::map<std::string, std::vector<std::string>> snippet_group_map;
  std::vector<std::string> group_vector;

  TomlConfigType config_type;

  std::stringstream line_stream;

  for (std::string line; std::getline(file, line);) {
    line.erase(std::remove_if(line.begin(), line.end(), isspace),
               line.end()); // Remove whitespace

    if (line.empty() || line[0] == '#') {
      continue;
    }

    key = value = "";

    if (line.at(0) == '[') {
      if (line.substr(1, line.size() - 2) == "snippets") {
        config_type = SNIPPETS;
      } else if (line.substr(1, line.size() - 2) == "snippets.groups") {
        config_type = SNIPPET_GROUPS;
      }

      continue;
    }

    split = "";
    line_stream.clear();
    line_stream << line;
    for (int i = 0; std::getline(line_stream, split, '='); i++) {
      if (!i) { // If i is 0
        if (line.find('=') == std::string::npos) {
          value = split;
        } else {
          key = split;
        }
      } else {
        value = split;
      }
    }

    // Cleaning quotes
    value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
    value.erase(std::remove(value.begin(), value.end(), '\''), value.end());

    // Removing inline comments
    if (value.find('#') != std::string::npos) {
      value = value.substr(0, value.find('#'));
    }

    if (config_type == SNIPPETS) {
      snippet_map.insert({key, value});
    } else if (config_type == SNIPPET_GROUPS) {
      if (value.find('[') != std::string::npos &&
          value.find(']') != std::string::npos) {
        value.erase(std::remove(value.begin(), value.end(), '['), value.end());
        value.erase(std::remove(value.begin(), value.end(), ']'), value.end());

        split = "";
        line_stream.clear();
        group_vector.clear();
        for (line_stream << value; std::getline(line_stream, split, ',');) {
          group_vector.push_back(split);
        }
        snippet_group_map.insert({key, group_vector});
        group_vector.clear();
        continue;
      }

      value.erase(std::remove(value.begin(), value.end(), ','), value.end());

      if (value.find('[') != std::string::npos) {
        prev_key = key;
        value.erase(std::remove(value.begin(), value.end(), '['), value.end());
      }

      if (value.find(']') == std::string::npos) {
        group_vector.push_back(value);
      } else {
        value.erase(std::remove(value.begin(), value.end(), ']'), value.end());
        group_vector.push_back(value);
        snippet_group_map.insert({prev_key, group_vector});
        group_vector.clear();
      }
    }
  }

  if (snippet_map.empty()) {
    snippets = std::nullopt;
  } else {
    snippets = snippet_map;
  }

  if (snippet_group_map.empty()) {
    snippet_groups = std::nullopt;
  } else {
    snippet_groups = snippet_group_map;
  }
}