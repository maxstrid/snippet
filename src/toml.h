#ifndef TOML_H_
#define TOML_H_

#include <iostream>
#include <map>
#include <optional>
#include <vector>

class Config {
public:
  Config(const std::string filename);
  void write(); // TODO: Let the user add snippets

  std::optional<std::map<std::string, std::string>> snippets;
  std::optional<std::map<std::string, std::vector<std::string>>> snippet_groups;

private:
  std::string filename;
};

#endif // TOML_H_