#ifndef CPPTOOLS_MANIFESTO_INFO_HPP
#define CPPTOOLS_MANIFESTO_INFO_HPP

#include "../include/manifesto.hpp"
#include "is_valid.hpp"

namespace Manifesto {

// -----------------------------------------------------------------------------

int info_command(Manifest &m) {
  if(!is_valid(m))
    return 0;

  std::string project = m["project"][1];
  std::string version = m["version"][1];

  std::cout << project << " " << version << '\n';

  std::string description = m["description"][1];
  if(!description.empty()) {
    std::cout << description << '\n';
  }
}

} // Manifeso

#endif // CPPTOOLS_MANIFESTO_INFO_HPP
