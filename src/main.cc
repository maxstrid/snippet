#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#include "toml.h"

#define CONFIG "/.config/snippet"

void copy(std::string file, std::string deststr) {
  std::ifstream source(file, std::ios::binary);
  std::ofstream dest(deststr, std::ios::binary);

  dest << source.rdbuf();

  source.close();
  dest.close();
}

int main(int argc, char *argv[]) {
  auto conf = toml::read("/home/uid/.config/snippet/config.toml");

  if (conf.snippets.has_value()) {
    auto snips = conf.snippets.value();

    for (auto pair : snips) {
      std::ifstream file(pair.second);
      if (!file.is_open()) {
        std::cerr << "Uknown file: " << pair.second << '\n';
        conf.snippets.value().erase(pair.first);
      }
    }
  }
  if (conf.snippet_groups.has_value()) {
    auto snip_groups = conf.snippet_groups.value();

    for (auto pair : snip_groups) {
      for (auto filepath : pair.second) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
          std::cerr << "Uknown file: " << filepath << '\n';
          conf.snippet_groups.value().erase(pair.first);
        }
      }
    }
  }
  std::string home_var = std::getenv("HOME");

  if (home_var.empty()) {
    std::cerr << "Couldn't find environemnt variable $HOME" << std::endl;
    return 1;
  }

  char cwd[PATH_MAX];

  if (getcwd(cwd, sizeof(cwd)) == nullptr) {
    std::cerr << "getcwd() error\n";
    return 1;
  }

  for (int i = 0; i < argc; i++) {
    if (conf.snippets.has_value()) {
      for (auto pair : conf.snippets.value()) {
        if (strcmp(argv[i], pair.first.c_str()) == 0) {
          std::cout << "Moving " << pair.first << '\n';
          copy(pair.second,
               cwd + std::string("/") +
                   std::string(std::filesystem::path(pair.second).filename()));
        }
      }
      if (conf.snippet_groups.has_value()) {
        for (auto pair: conf.snippet_groups.value()) {
          if (strcmp(argv[i], pair.first.c_str()) == 0) {
            std::cout << "Moving " << pair.first << '\n';
            for (auto second: pair.second) {
              copy(second, cwd + std::string("/") + std::string(std::filesystem::path(second).filename()));
            }
          }
        }
      }
    }
  }

  return 0;
}