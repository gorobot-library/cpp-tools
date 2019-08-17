#ifndef CPP_TOOLS_CLAP_CLAP_HPP
#define CPP_TOOLS_CLAP_CLAP_HPP

#include <iostream>
#include <regex>
#include <string>
#include <variant>

namespace CLAP {

// -----------------------------------------------------------------------------

using std::string;

using var_t = std::variant<bool, double, string>;

class CLAP {
private:

  template<typename T>
  struct Argument {
    string name;
    string desc;
    T value;
  };

  struct BaseVisitor {
    virtual ~BaseVisitor() = default;
  };
  template<typename T>
  struct Visitor : BaseVisitor {
    T data;
    // void visit(T &t) {
    //   this->data = t;
    // };
  };

  class Arg;

  std::vector<Arg> arguments_;

  const std::regex is_command = std::regex("-(.)=(.+)");
  const std::regex is_flag = std::regex("^-(.)=*(\\S*)");
  const std::regex is_long_flag = std::regex("--(.+)=(.+)");

public:

  template<typename T>
  T stov(string s);

  void add_command(string name, string desc);

  template<typename T>
  void add_option(string name, T value, string desc);
  // template<typename T>
  // void add_long_flag(string name, T value, string desc);

  void parse(size_t argc, char *argv[]);

  template<typename T>
  T get_value(string name);
};

class CLAP::Arg {
private:
  struct Concept {
    virtual ~Concept() = default;
    virtual string get_name() const = 0;
    virtual string get_description() const = 0;
    virtual void get_value(BaseVisitor &v) const = 0;
    virtual void set_value(BaseVisitor &v) = 0;
  };

  template<typename T>
  struct Model final : Concept {
    T data_;

    Model(T data) : data_(data) {}

    virtual string get_name() const override {
      return this->data_.name;
    };

    virtual string get_description() const override {
      return this->data_.desc;
    };

    virtual void get_value(BaseVisitor &v) const override {
      Visitor<T> &sv = dynamic_cast<Visitor<T> &>(v);
      sv.data = data_;
    };

    virtual void set_value(BaseVisitor &v) override {
      Visitor<T> &sv = dynamic_cast<Visitor<T> &>(v);
      data_.value = sv.data.value;
    };
  };

  std::shared_ptr<const Concept> self_;

public:

  template<typename T>
  Arg(T data) : self_(std::make_shared<Model<T>>(std::move(data))) {}

  string get_name() const {
    return self_->get_name();
  };

  string get_description() const {
    return self_->get_description();
  };

  template<typename T> T get_value() const {
    Visitor<Argument<T>> v;
    self_->get_value(v);
    return v.data.value;
  }

  template<typename T> void set_value(T value) const {
    Visitor<Argument<T>> v;
    v.data.value = value;
    self_->set_value(v);
  }

};

// -----------------------------------------------------------------------------
// Constructor

// -----------------------------------------------------------------------------
// Methods
template<>
int CLAP::stov(string s) {
  return std::stoi(s);
}
template<>
long CLAP::stov(string s) {
  return std::stol(s);
}
template<>
float CLAP::stov(string s) {
  return std::stof(s);
}
template<>
double CLAP::stov(string s) {
  return std::stod(s);
}
template<>
string CLAP::stov(string s) {
  return s;
}

void CLAP::add_command(string name, string desc) {
  Argument<bool> arg = {name, desc, false};
  this->arguments_.push_back(arg);
  // this->arguments_.push_back(std::make_shared<Model<Argument<bool>>>(arg));
}

template<typename T>
void CLAP::add_option(string name, T value, string desc) {
  Argument<T> arg = {name, desc, value};
  this->arguments_.push_back(arg);
  // this->arguments_.push_back(std::make_shared<Model<Argument<T>>>(arg));
}

// template<typename T>
// void CLAP::add_long_flag(string name, T value, string desc) {
//   LongFlag<T> long_flag = {name, value, desc};
//   this->arguments_.push_back(std::make_shared<Model<LongFlag<T>>>(long_flag));
// }

void CLAP::parse(size_t argc, char *argv[]) {
  if(argc == 1) {
    return;
  }

  std::match_results<const char *> match;

  for(size_t i = 1; i < argc; i++) {
    if(std::regex_match(argv[i], match, is_flag)) {
      string name = match[1];

      for(size_t j = 0; j < this->arguments_.size(); j++) {
        if(this->arguments_[j].get_name() == name) {
          // this->arguments_[j].set_value()
        }
      }
    }
    else if(std::regex_match(argv[i], match, is_flag)) {

    }
  }
}

template<typename T>
T CLAP::get_value(string name) {
  for(size_t j = 0; j < this->arguments_.size(); j++) {
    if(this->arguments_[j].get_name() == name) {
      return this->arguments_[j].get_value<T>();
    //   std::shared_ptr<const Model<Argument<T>>> ptr;
    //
    //   if(ptr = dynamic_pointer_cast<const Model<Argument<T>>>(this->arguments_[j])) {
    //     return ptr->data_.value;
    //   }
    }
  }
  return false;
}

} // CLAP

#endif // CPP_TOOLS_CLAP_CLAP_HPP
