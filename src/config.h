#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <vector>

// Vector only needed because size can't be known at compile time
std::vector<std::string> read_config(std::string filename);

void parse_config(std::vector<std::string> &config_vec);

#endif // CONFIG_H_