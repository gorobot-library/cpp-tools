#ifndef CPPTOOLS_MANIFESTO_HPP
#define CPPTOOLS_MANIFESTO_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
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

class Manifest {
private:

  KVIStore kv_;

public:

  // Manifest();
  // Manifest(KVIStore &kv);

  KVIStore get_kvistore();

  bool read_manifest(std::filesystem::path const &p);
  bool write_manifest(std::filesystem::path const &p);

  void add_entry(string key, string value, string ind);

  KVITuple operator[](string key);
  KVITuple operator[](size_t pos);

  bool validate();
};

// -----------------------------------------------------------------------------
// Constructor
// Manifest::Manifest() : kv_(std::move(KVIStore())) {
//   // KVIStore kv;
//   // this->kv_ = kv;
// }
// Manifest::Manifest(KVIStore &kv) : kv_(kv) {
//
// }

// -----------------------------------------------------------------------------
// Methods
KVIStore Manifest::get_kvistore() {
  return this->kv_;
}

bool Manifest::read_manifest(std::filesystem::path const &p) {
  std::ifstream src(p);
  if (!src)
    return false;

  std::stringstream buffer;
  buffer << src.rdbuf();

  Parser pr;
  this->kv_ = pr.parse(buffer);

  return true;
}

bool Manifest::write_manifest(std::filesystem::path const &p) {
  std::ofstream dest(p);
  if (!dest)
    return false;

  Emitter em;
  string s = em.emit(this->kv_);

  dest << s << '\n';

  return true;
}

void Manifest::add_entry(string key, string value, string ind = KVIL0) {
  KVITuple el = {key, value, ind};
  this->kv_.emplace_back(el);
}

// void Manifest::add_entry(std::allocator<KVITuple> &a) {
//   KVITuple el = a;
//   this->kv_.emplace_back(el);
// }

KVITuple Manifest::operator[](string key) {
  return this->kv_[key];
}

KVITuple Manifest::operator[](size_t pos) {
  return this->kv_[pos];
}

bool Manifest::validate() {
  if(!this->kv_.has_key_value("project")) {
    return false;
  }
  if(!this->kv_.has_key_value("version")) {
    return false;
  }

  return true;
}

} // Manifesto

#endif // CPPTOOLS_MANIFESTO_HPP
