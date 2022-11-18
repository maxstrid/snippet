#ifndef TOML_H_
#define TOML_H_

#include <iostream>
#include <map>
#include <optional>
#include <map>
#include <vector>

namespace toml {
struct Config {
  std::optional<std::map<std::string, std::string>> snippets;
  std::optional<std::map<std::string, std::vector<std::string>>> snippet_groups;
};

Config read(const std::string filename);

void parse(std::map<std::string, std::string> &toml);
} // namespace toml

#endif // TOML_H_