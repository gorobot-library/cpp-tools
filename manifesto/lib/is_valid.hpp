#ifndef CPPTOOLS_MANIFESTO_IS_VALID_HPP
#define CPPTOOLS_MANIFESTO_IS_VALID_HPP

#include "../include/manifesto.hpp"

namespace Manifesto {

// -----------------------------------------------------------------------------

std::string ill_formed =
R"(Manifest is ill-formed.
Make sure the project and version are present.

To generate a manifest, use: manifest init
)";

bool is_valid(Manifest &m) {
  if(!m.validate()) {
    std::cout << ill_formed << '\n';
    return false;
  }
  return true;
}

} // Manifeso

#endif // CPPTOOLS_MANIFESTO_IS_VALID_HPP
