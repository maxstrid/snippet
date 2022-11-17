#include <iostream>
#include <fstream>
//#include <stringstream>
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
        std::string split;
        int count = 0;

        while(std::getline(file, file_str)) {
            if (file_str[0] != '#' && !file_str.empty() && file_str[0] != '[') {
                std::stringstream file_stream(file_str);
                std::string key, value;

                count = 0;
                while (std::getline(file_stream, split, '=')) {
                    if(count) {
                        value = split;
                    } else {
                        key = split;
                    }
                    count++;
                }

                std::pair<std::string, std::string> pr(key, value);
                config_map.insert(pr);
            }
        }

        return config_map;
    }
}