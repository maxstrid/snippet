#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <toml++/toml.h>

class Config {
public:
  Config(const std::string &filename);

  // TOOD: Allow the user to add things to the config
  void add();

  toml::table table() { return table_; };

private:
  std::string filename_;
  toml::table table_;
};

#endif // CONFIG_H_
