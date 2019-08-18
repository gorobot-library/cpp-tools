#ifndef CPP_TOOLS_CLAP_ARG_HPP
#define CPP_TOOLS_CLAP_ARG_HPP

#include <iostream>
#include <regex>
#include <string>
#include <variant>

namespace CLAP {

// -----------------------------------------------------------------------------

using std::string;
using ArgTuple = std::array<string, 3>;
using ArgVector = std::vector<ArgTuple>;

class ArgStore : public ArgVector {
public:
  using ArgVector::operator[];
  string operator[](string key);
};

// -----------------------------------------------------------------------------
// Methods
string ArgStore::operator[](string key) {
  string result;
  for(size_t i = 0; i < this->size(); i++) {
    if((*this)[i][0] == key) {
      result = (*this)[i][2];
    }
  }
  return result;
}

} // CLAP

#endif // CPP_TOOLS_CLAP_ARG_HPP
