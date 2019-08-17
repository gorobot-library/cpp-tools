#ifndef CPPTOOLS_MANIFESTO_PARSER_HPP
#define CPPTOOLS_MANIFESTO_PARSER_HPP

#include <regex>
#include <sstream>
#include <string>

#include "kvi.hpp"

namespace Manifesto {

// -----------------------------------------------------------------------------

using std::string;
using std::regex;

class Parser {
private:

  const regex yaml_line = regex("(\\s*)-?\\s*([^:\\s]+)\\s*:?\\s*(.*)");

public:

  KVIStore parse(string s);
  KVIStore parse(std::stringstream &s);

};

// -----------------------------------------------------------------------------
// Methods
KVIStore Parser::parse(string s) {
  KVIStore result;

  std::stringstream src(s);

  string line;
  std::smatch match;

  string key;
  string value;
  string indent;

  while(std::getline(src, line)) {
    if(regex_match(line, match, yaml_line)) {
      key = match[2];
      value = match[3];
      indent = match[1];

      KVITuple m = {key, value, indent};

      result.emplace_back(m);
    }
  }

  return result;
}

KVIStore Parser::parse(std::stringstream &s) {
  KVIStore result;

  string line;
  std::smatch match;

  string key;
  string value;
  string indent;

  while(std::getline(s, line)) {
    if(regex_match(line, match, yaml_line)) {
      key = match[2];
      value = match[3];
      indent = match[1];

      KVITuple m = {key, value, indent};

      result.emplace_back(m);
    }
  }

  return result;
}

} // Manifesto

#endif // CPPTOOLS_MANIFESTO_PARSER_HPP
