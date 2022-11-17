#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>

#include "toml.h"

namespace toml {
    std::map<std::string, std::string> read(const std::string filename) {
        std::map<std::string, std::string> config_map;

        if (std::filesystem::path(filename).extension() != ".toml") {
            std::cerr << filename << ": file not toml\n";
            std::exit(1);
        }

        std::ifstream file(filename, std::ios::binary);

        if (!file.is_open()) {
            std::perror(filename.c_str());
            std::exit(1);
        }

        std::string file_str;

        while(std::getline(file, file_str)) {
            if (file_str[0] != '#' && !file_str.empty() && file_str[0] != '[') {
                std::string key = file_str.substr(0, file_str.find('='));
                std::string value = file_str.substr(0, file_str.find('='));

                std::pair<std::string, std::string> pr(key, value);
                config_map.insert(pr);
            }
        }

        return config_map;
    }
}