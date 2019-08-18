#include <filesystem>
#include <iostream>
#include <string>

#include "../include/manifesto.hpp"
#include "../lib/info.hpp"

std::string help_string =
R"(Manifesto
A manifest generator and dependency analyzer.

Usage: manifesto [options] command

Options:
  -h, --help      Display the help.
  -v, --version   Display package version.
  -f, --file      Specify manifest file.

Commands:
  bump            Bump the version in the manifest.
  info            Get package info.
  init            Create a simple manifest file.
)";

std::string not_found =
R"(
No manifest file found.
To generate a manifest, use: manifest init
)";

int main(int argc, char const *argv[]) {
  if(argc == 1) {
    std::filesystem::path p = "./manifest.yaml";
    if(!std::filesystem::exists(p)) {
      std::cout << not_found << '\n';
      return 0;
    }

    Manifesto::Manifest m;
    m.read_manifest(p);

    if(!is_valid(m))
      return 0;

    std::string project = m["project"][1];
    std::string version = m["version"][1];

    std::cout << project << " " << version << '\n';

    std::string description = m["description"][1];
    if(!description.empty()) {
      std::cout << description << '\n';
    }
  }
  else {
    std::filesystem::path p = "./manifest.yaml";
    if(!std::filesystem::exists(p)) {
      std::cout << not_found << '\n';
      return 0;
    }

    Manifesto::Manifest m;
    m.read_manifest(p);

    std::string command = argv[1];

    if(command == "-h" || command == "--help") {
      std::cout << help_string << '\n';
    }
    else if(command == "-v" || command == "--version") {
      std::string version = m["version"][1];
      std::cout << version << '\n';
    }
  }

  return 0;
}
