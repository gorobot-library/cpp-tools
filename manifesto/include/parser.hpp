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

  const regex is_dict = regex("\\s*-?\\s*[^:\\s]+\\s*:.*");
  const regex is_list = regex("\\s*-\\s*.+");
  const regex yaml_dict = regex("(\\s*)-?\\s*([^:\\s]+)\\s*:?\\s*(.*)");
  const regex yaml_list = regex("(\\s*)-\\s*(.+)");

public:

  KVIStore parse(string s);
  KVIStore parse(std::stringstream &s);

};

// -----------------------------------------------------------------------------
// Methods
KVIStore Parser::parse(string s) {
  KVIStore result;

  std::stringstream src(s);

  return parse(src);
}

KVIStore Parser::parse(std::stringstream &src) {
  KVIStore result;

  string line;
  std::smatch match;

  string key;
  string value;
  string indent;

  while(std::getline(src, line)) {
    if(regex_match(line, match, is_dict)) {
      if(regex_match(line, match, yaml_dict)) {
        key = match[2];
        value = match[3];
        indent = match[1];

        KVITuple m = {key, value, indent};

        result.emplace_back(m);
      }
    }
    else if(regex_match(line, match, is_list)) {
      if(regex_match(line, match, yaml_list)) {
        value = match[2];
        indent = match[1];

        KVITuple m = {"", value, indent};

        result.emplace_back(m);
      }
    }
  }

  return result;
}

} // Manifesto

#endif // CPPTOOLS_MANIFESTO_PARSER_HPP
