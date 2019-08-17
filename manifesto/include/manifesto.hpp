#ifndef CPPTOOLS_MANIFESTO_HPP
#define CPPTOOLS_MANIFESTO_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "parser.hpp"
#include "emitter.hpp"

namespace Manifesto {

// -----------------------------------------------------------------------------

using std::string;

class Manifesto {
private:

  KVIStore kv_;

public:

  bool read_manifest(std::filesystem::path const &p);
  bool write_manifest(std::filesystem::path const &p);

};

// -----------------------------------------------------------------------------
// Methods
bool Manifesto::read_manifest(std::filesystem::path const &p) {
  std::ifstream src(p);
  if (!src)
    return false;

  std::stringstream buffer;
  buffer << src.rdbuf();

  Parser pr;
  this->kv_ = pr.parse(buffer);

  return true;
}

bool Manifesto::write_manifest(std::filesystem::path const &p) {
  std::ofstream dest(p);
  if (!dest)
    return false;

  Emitter em;
  string s = em.emit(this->kv_);

  std::cout << s << '\n';

  return true;
}

} // Manifesto

#endif // CPPTOOLS_MANIFESTO_HPP
