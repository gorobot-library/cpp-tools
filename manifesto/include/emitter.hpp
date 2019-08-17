#ifndef CPPTOOLS_MANIFESTO_EMITTER_HPP
#define CPPTOOLS_MANIFESTO_EMITTER_HPP

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "kvi.hpp"

namespace Manifesto {

// -----------------------------------------------------------------------------

using std::string;
using std::regex;

class Emitter {
private:

public:

  string emit(KVIStore &kv);

};

// -----------------------------------------------------------------------------
// Methods
string Emitter::emit(KVIStore &kv) {
  string result = "";
  KVIStore sub;

  for(size_t i = 0; i < kv.size(); i++) {
    sub = kv.subtree(i);
    if(sub.size() == 1) {
      if(sub[0][1].empty()) {
        result += kv[i][2] + "- " + kv[i][0] + '\n';
      }
      else {
        result += kv[i][2] + kv[i][0] + ": " + kv[i][1] + '\n';
      }
    }
    else {
      result += kv[i][2] + kv[i][0] + ": " + kv[i][1] + '\n';
    }
  }

  return result;
}

} // Manifesto

#endif // CPPTOOLS_MANIFESTO_EMITTER_HPP
