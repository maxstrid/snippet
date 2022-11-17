#ifndef TOML_H_
#define TOML_H_

#include <iostream>
#include <map>

namespace toml {
    std::map<std::string, std::string> read(const std::string filename);

    void parse(std::map<std::string, std::string> &toml);
}

#endif // TOML_H_