#ifndef CPPTOOLS_MANIFESTO_KVI_HPP
#define CPPTOOLS_MANIFESTO_KVI_HPP

#ifndef KVIL0
#define KVIL0 ""
#endif
#ifndef KVIL1
#define KVIL1 "  "
#endif
#ifndef KVIL2
#define KVIL2 "    "
#endif
#ifndef KVIL3
#define KVIL3 "      "
#endif
#ifndef KVIL4
#define KVIL4 "        "
#endif
#ifndef KVIL5
#define KVIL5 "          "
#endif

#include <array>
#include <string>
#include <vector>

namespace Manifesto {

// -----------------------------------------------------------------------------

using std::string;
using KVITuple = std::array<string, 3>;
using KVIVector = std::vector<KVITuple>;

struct KVIStore : public KVIVector {
  using KVIVector::operator[];
  KVITuple operator[](string key);

  KVIStore subtree(string key);
  KVIStore subtree(size_t pos);

  bool has_key(string key);
  bool has_key_value(string key);
  bool has_subtree(string key);
};

// -----------------------------------------------------------------------------
// Methods

KVITuple KVIStore::operator[](string key) {
  KVITuple result;
  for(size_t i = 0; i < this->size(); i++) {
    if((*this)[i][0] == key) {
      result = (*this)[i];
    }
  }
  return result;
}

KVIStore KVIStore::subtree(string key) {
  KVIStore sub;

  size_t i;
  for(i = 0; i < this->size(); i++) {
    if((*this)[i][0] == key) {
      sub.emplace_back((*this)[i]);
      break;
    }
  }

  // Not found.
  if(sub.empty())
    return sub;

  size_t len = (*this)[i][2].length();

  for(size_t j = i+1; j < this->size(); j++) {
    if(len < (*this)[j][2].length()) {
      sub.emplace_back((*this)[j]);
    }
    else {
      break;
    }
  }

  return sub;
}

KVIStore KVIStore::subtree(size_t pos) {
  KVIStore sub;

  sub.emplace_back((*this)[pos]);

  size_t len = (*this)[pos][2].length();

  for(size_t j = pos+1; j < this->size(); j++) {
    if(len < (*this)[j][2].length()) {
      sub.emplace_back((*this)[j]);
    }
    else {
      break;
    }
  }

  return sub;
}

bool KVIStore::has_key(string key) {
  for(size_t i = 0; i < this->size(); i++) {
    if((*this)[i][0] == key) {
      return true;
    }
  }
  return false;
}
bool KVIStore::has_key_value(string key) {
  for(size_t i = 0; i < this->size(); i++) {
    if((*this)[i][0] == key && !(*this)[i][1].empty()) {
      return true;
    }
  }
  return false;
}
bool KVIStore::has_subtree(string key) {
  KVIStore sub = this->subtree(key);
  if(sub.size() > 1) {
    return true;
  }
  return false;
}

} // Manifesto

#endif // CPPTOOLS_MANIFESTO_KVI_HPP
