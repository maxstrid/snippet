#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>

#include "config.h"

std::map<std::string, std::string> read_config(std::string filename) {
  std::map<std::string, std::string> conf_map;

  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open()) {
    std::perror(filename.c_str());
  }

  std::string file_str = "";

  while (std::getline(file, file_str)) {
    if (file_str[0] != '#' && !file_str.empty()) {
      std::string second = file_str.substr(0, file_str.find(' '));
      std::string first = file_str.substr(second.size(), file_str.find(' '));

      first.erase(std::remove_if(first.begin(), first.end(), isspace),
                  first.end());

      for (int i = 0; i < first.size(); i++) {
        first[i] = tolower(first[i]);
      }

      std::pair<std::string, std::string> pr(first, second);
      conf_map.insert(pr);
    }
  }

  file.close();

  return conf_map;
}