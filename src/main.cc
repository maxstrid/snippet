#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <unistd.h>

#include "toml.h"

void check_file(const std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "unknown file: " << filename << '\n';
  }
}

void copy(std::string file, std::string deststr) {
  std::ifstream source(file, std::ios::binary);
  std::ofstream dest(deststr, std::ios::binary);

  dest << source.rdbuf();

  source.close();
  dest.close();
}

int main(int argc, char *argv[]) {
  std::string xdg_config = std::getenv("XDG_CONFIG_HOME");

  if (xdg_config.empty()) {
    xdg_config = std::getenv("HOME");
    if (xdg_config.empty()) {
      std::cerr << "No config directory found" << '\n';
    } else {
      xdg_config += "/.config";
    }
  }

  Config conf(xdg_config + "/snippet/config.toml");

  if (conf.snippets.has_value()) {
    auto snips = conf.snippets.value();

    for (auto pair : snips) {
      check_file(pair.second);
    }
  }
  if (conf.snippet_groups.has_value()) {
    auto snip_groups = conf.snippet_groups.value();

    for (auto pair : snip_groups) {
      for (auto filepath : pair.second) {
        check_file(filepath);
      }
    }
  }

  char cwd[PATH_MAX];

  if (getcwd(cwd, sizeof(cwd)) == nullptr) {
    std::cerr << "getcwd() error\n";
    return 1;
  }

  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "snip") == 0) {
      if (!conf.snippets.has_value())
        continue;

      if (argc - 2 < i) {
        std::cerr << "not enough arguments passed\n";
        return 1;
      }

      for (auto pair : conf.snippets.value()) {
        // This should be safe because we check the limits above
        if (strcmp(argv[i + 1], pair.first.c_str()) != 0)
          continue;

        std::cout << "moving " << pair.first << '\n';
        copy(pair.second,
             cwd + std::string("/") +
                 std::string(std::filesystem::path(pair.second).filename()));
      }
    } else if (strcmp(argv[i], "group") == 0) {
      if (!conf.snippet_groups.has_value())
        continue;

      if (argc - 2 < i) {
        std::cerr << "not enough arguments passed\n";
        return 1;
      }

      for (auto pair : conf.snippet_groups.value()) {
        if (strcmp(argv[i + 1], pair.first.c_str()) != 0)
          continue;

        std::cout << "moving " << pair.first << '\n';
        for (auto path : pair.second) {
          copy(path, cwd + std::string("/") +
                         std::string(std::filesystem::path(path).filename()));
        }
      }
    }
  }

  return 0;
}