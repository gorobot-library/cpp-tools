#ifndef CPP_TOOLS_TPL_HPP
#define CPP_TOOLS_TPL_HPP

#include <string>
#include <vector>

namespace TPL {

// -----------------------------------------------------------------------------

using std::string;

class TPL {
private:

  struct tpl_string {
    string from;
    string to;
  };

  std::vector<tpl_string> strings_;

  void replace(string &s, const string &from, const string &to);

public:

  void add_tpl_string(const string &from, const string &to);

  void parse(string &s);
};

// -----------------------------------------------------------------------------
// Methods
void TPL::replace(string& s, const string& from, const string& to) {
  if(from.empty())
    return;

  size_t start_pos = 0;
  while((start_pos = s.find(from, start_pos)) != string::npos) {
    s.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

void TPL::add_tpl_string(const string &from, const string &to) {
  tpl_string s = {from, to};
  this->strings_.emplace_back(s);
}

void TPL::parse(string &s) {
  // Replace strings in strings.
  for(size_t i = 0; i < this->strings_.size(); i++) {
    for(size_t j = 0; j < this->strings_.size(); j++) {
      replace(this->strings_[i].to,
              this->strings_[j].from,
              this->strings_[j].to);
    }
  }

  // Replace strings in target.
  for(size_t i = 0; i < this->strings_.size(); i++) {
    replace(s, this->strings_[i].from, this->strings_[i].to);
  }
}

} // TPL

#endif // CPP_TOOLS_TPL_HPP
