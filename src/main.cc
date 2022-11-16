#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <limits.h>
#include <vector>

#include "config.h"

#define CONFIG "/.config/snippet"

void copy(std::string file, std::string deststr) {
    std::ifstream source(file, std::ios::binary);
    std::ofstream dest(deststr, std::ios::binary);

    dest << source.rdbuf();

    source.close();
    dest.close();
}

int main(int argc, char *argv[]) {
    std::string home_var = std::getenv("HOME");

    if (home_var.empty()) {
        std::cerr << "Couldn't find environemnt variable $HOME" << std::endl;
        return 1;
    }

    std::string screen = home_var + CONFIG + "/Screen.java";
    std::string runner = home_var + CONFIG + "/Runner.java";

    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == nullptr) {
        std::cerr << "getcwd() error\n";
        return 1;
    }

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "screen") == 0) {
            std::cout << "Moving screen\n";

            copy(screen, cwd + std::string("/Screen.java"));
        } else if (strcmp(argv[i], "runner") == 0) {
            std::cout << "Moving runner\n";

            copy(runner, cwd + std::string("/Runner.java"));
        }
    }


    auto config = read_config("example.conf");

    for(auto pair: config) {
        std::cout << pair.first << " : " << pair.second << '\n';
    }
    return 0;
}