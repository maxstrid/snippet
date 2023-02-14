#include "config.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <toml++/toml.h>

Config::Config(const std::string &filename) : filename_(filename) {
  try {
    table_ = toml::parse_file(filename);
  } catch (const toml::parse_error &err) {
    std::cerr << "Error parsing file '" << *err.source().path << "':\n"
              << err.description() << "\n  (" << err.source().begin << ")\n";

    // Exit probably isn't the best way to do it here but
    // there really isn't a better way to do it from a
    // constructor as far as I know.
    std::exit(1);
  }
}
