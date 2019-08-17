#ifndef CPP_TOOLS_SCAFFOLD_TPL_CLASS_HPP
#define CPP_TOOLS_SCAFFOLD_TPL_CLASS_HPP

#include <string>

namespace Scaffold {

std::string tpl_class = R"~(
class {{CLASS_NAME}} {
private:
  // Private member variables.

public:
  // Constructor
  {{CLASS_NAME}}();

  // Methods

};

// -----------------------------------------------------------------------------
// Constructor
{{CLASS_NAME}}::{{CLASS_NAME}}() {

}

// -----------------------------------------------------------------------------
// Methods
)~";

} // Scaffold

#endif // CPP_TOOLS_SCAFFOLD_TPL_CLASS_HPP
