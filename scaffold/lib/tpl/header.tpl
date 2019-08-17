#ifndef CPP_TOOLS_SCAFFOLD_TPL_HEADER_HPP
#define CPP_TOOLS_SCAFFOLD_TPL_HEADER_HPP

#include <string>

namespace Scaffold {

std::string tpl_header = R"~(// Generated by Scaffold.
#ifndef {{PROJECT_NAME}}_{{FILE_NAME}}_HPP
#define {{PROJECT_NAME}}_{{FILE_NAME}}_HPP

namespace {{NAMESPACE}} {

// -----------------------------------------------------------------------------

{{CODE}}

} // {{NAMESPACE}}

#endif // {{PROJECT_NAME}}_{{FILE_NAME}}_HPP
)~";

} // Scaffold

#endif // CPP_TOOLS_SCAFFOLD_TPL_HEADER_HPP