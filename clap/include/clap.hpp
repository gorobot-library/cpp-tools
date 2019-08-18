#ifndef CPP_TOOLS_CLAP_CLAP_HPP
#define CPP_TOOLS_CLAP_CLAP_HPP

#include <iostream>
#include <regex>
#include <string>
#include <variant>

#include "arg.hpp"

namespace CLAP {

// -----------------------------------------------------------------------------

using std::string;
using std::regex;

class CLAP {
private:

  ArgStore arg_list_;
  ArgStore results_;

  /*
  (-[^\s]),\s*(--[^\s]+)\s*([^\s]+)
  */

  const regex option_name = regex("(\\S+)\\s?(.+)");

  const regex parse_arg = regex("(-[^-\\s,=]|--[^-\\s,=]+)=?(.*)");

public:

  void add_option(string name, string description, string params);

  void parse(int argc, char const *argv[]);

};

// -----------------------------------------------------------------------------
// Methods
void CLAP::add_option(string name, string description, string params) {
  ArgTuple arg = {name, description, params};
  this->arg_list_.emplace_back(arg);
}

void parse(int argc, char const *argv[]) {
  std::match_results<const char *> match;

  for(int i = 0; i < argc; i++) {

  }
}

} // CLAP

#endif // CPP_TOOLS_CLAP_CLAP_HPP
