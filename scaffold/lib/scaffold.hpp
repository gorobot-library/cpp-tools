#ifndef CPP_TOOLS_SCAFFOLD_HPP
#define CPP_TOOLS_SCAFFOLD_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <tpl/tpl.hpp>

#include "tpl/class.tpl"
#include "tpl/cmake_header_only.tpl"
#include "tpl/header.tpl"
#include "tpl/source.tpl"

namespace Scaffold {

// -----------------------------------------------------------------------------

class Scaffold {
private:

  std::string project_name_;
  TPL::TPL tpl;

public:

  Scaffold(std::string name);

  bool create_directory(std::filesystem::path const &p);

  void generate_cmake(std::filesystem::path const &dest);
};

// -----------------------------------------------------------------------------
// Constructor
Scaffold::Scaffold(std::string name) : project_name_(name) {

  tpl.add_tpl_string("{{PROJECT_NAME}}", project_name_);
}

// -----------------------------------------------------------------------------
// Methods
bool Scaffold::create_directory(std::filesystem::path const &p) {
  if(!std::filesystem::exists(p)) {
    return std::filesystem::create_directory(p);
  }
  else return true;
}

void Scaffold::generate_cmake(std::filesystem::path const &dest) {
  std::stringstream src_file(tpl_cmake_header_only);
  std::ofstream dest_file(dest);
  if (!dest_file)
    return;

  std::string line;
  while(std::getline(src_file, line)) {
    tpl.parse(line);
    dest_file << line << '\n';
  }

  dest_file.close();
}

} // Scaffold

#endif // CPP_TOOLS_SCAFFOLD_HPP
