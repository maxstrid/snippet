#include <fstream>
#include <iostream>
#include <vector>

#include "config.h"

std::vector<std::string> read_config(const std::string filename) {
  std::vector<std::string> line_vec;

  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open()) {
    std::perror(filename.c_str());
  }

  std::string file_str = "";

  while (std::getline(file, file_str)) {
    if(file_str[0] != '#' && !file_str.empty()) {
      line_vec.push_back(file_str);
    }
  }

  file.close();

  return line_vec;
}