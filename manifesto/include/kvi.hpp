#ifndef CPPTOOLS_MANIFESTO_KVI_HPP
#define CPPTOOLS_MANIFESTO_KVI_HPP

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

} // Manifesto

#endif // CPPTOOLS_MANIFESTO_KVI_HPP
