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
    if(!kv[i][2].empty()) {
      result += kv[i][2] + "- ";
    }

    if(!kv[i][0].empty()) {
      result += kv[i][0];
    }

    if(!kv[i][0].empty()) {
      result += ": " + kv[i][1];
    }
    else if(kv.subtree(i).size() > 1) {
      result += ":";
    }
    else {
      result += kv[i][1];
    }

    result += '\n';
  }

  return result;
}

} // Manifesto

#endif // CPPTOOLS_MANIFESTO_EMITTER_HPP
