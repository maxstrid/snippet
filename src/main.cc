#include <iostream>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#define CONFIG "/.config/snippet"

void copy(std::string file, std::string deststr) {
    char buf[BUFSIZ];
    size_t size = 0;

    int source = open(file.c_str(), O_RDONLY, 0);
    int dest = open(deststr.c_str(), O_WRONLY | O_CREAT, 0655);

    while ((size == read(source, buf, BUFSIZ)) > 0) {
        std::cout << "a" << std::endl;
        write(dest, buf, size);
    }

    close(source);
    close(dest);
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

    return 0;
}