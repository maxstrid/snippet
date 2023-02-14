#include <filesystem>
#include <fstream>
#include <iostream>

#include <boost/program_options.hpp>

#include "config.h"

namespace boostpo = boost::program_options;

using std::string;
namespace fs = std::filesystem;

void copy_snippet(const string &snippet_path) {
  const string filename = string(fs::path(snippet_path).filename());

  std::cout << "Moving " << filename << '\n';

  fs::copy(fs::path(snippet_path),
           fs::path(string(fs::current_path()) + '/' + filename));
}

bool file_exists(const string &filename) {
  std::ifstream file(filename);
  return file.good();
}

int main(int argc, char *argv[]) {
  std::string config_location = Config::get_config();

  boostpo::options_description desc("Allowed Options");
  desc.add_options()("help", "give help message")(
      "config,c", boostpo::value<string>()->default_value(config_location),
      "set custom config file location")("snippet,s", boostpo::value<string>(),
                                         "copy snippet to your location")(
      "group,g", boostpo::value<string>(), "copy group to your location");

  boostpo::variables_map v_map;

  boostpo::store(boostpo::parse_command_line(argc, argv, desc), v_map);

  try {
    boostpo::notify(v_map);
  } catch (std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  if (v_map.count("help")) {
    std::cout << desc << '\n';
    return 0;
  }

  string filename = v_map["config"].as<string>();

  if (!file_exists(filename)) {
    std::cerr << "Couldn't find file " << filename << '\n';
    return 1;
  }

  Config conf(filename);

  const auto table = conf.table();

  if (v_map.count("snippet")) {
    const string snippet_name = v_map["snippet"].as<string>();

    const string snippet = table["snippets"][snippet_name].value_or("");

    if (snippet.empty()) {
      std::cerr << "snippet '" << snippet_name << "' not found in " << filename
                << '\n';

      return 1;
    }

    if (file_exists(snippet)) {
      copy_snippet(snippet);
    } else {
      std::cerr << "'" << snippet << "' not found, skipping.\n";
    }
  }

  if (v_map.count("group")) {
    const string group_name = v_map["group"].as<string>();

    const auto group = table["snippets"]["groups"][group_name];

    if (!group.is_array()) {
      std::cerr << "snippet group '" << group_name
                << "' not found or not an array in " << filename << '\n';

      return 1;
    }
    const auto snippets = group.as_array();

    for (auto &&snippet_path : *snippets) {
      string snippet = snippet_path.value_or("");

      if (file_exists(snippet)) {
        copy_snippet(snippet);
      } else {
        std::cerr << "'" << snippet << "' not found, skipping.\n";
      }
    }
  }
}
