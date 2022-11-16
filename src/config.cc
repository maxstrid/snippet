#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#include "config.h"

std::vector<std::pair<std::string, std::string>>
read_config(std::string filename) {
  std::vector<std::pair<std::string, std::string>> line_vec;

  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open()) {
    std::perror(filename.c_str());
  }

  std::string file_str = "";

  while (std::getline(file, file_str)) {
    if (file_str[0] != '#' && !file_str.empty()) {
      std::string first = file_str.substr(0, file_str.find(' '));
      std::string second = file_str.substr(first.size(), file_str.find(' '));

      second.erase(std::remove_if(second.begin(), second.end(), isspace),
                   second.end());

      std::pair<std::string, std::string> pr(first, second);
      line_vec.push_back(pr);
    }
  }

  file.close();

  return line_vec;
}