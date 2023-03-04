#pragma once

#include <toml++/toml.h>

class Config {
public:
  Config(const std::string &filename);

  // TOOD: Allow the user to add things to the config
  void add();

  static std::string get_config();

  toml::table table() { return table_; };

private:
  std::string filename_;
  toml::table table_;
};
