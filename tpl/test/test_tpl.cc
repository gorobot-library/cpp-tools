#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include <tpl.hpp>

TEST_CASE("TPL: Hello, world!", "[tpl]") {

  TPL::TPL t;
  t.add_tpl_string("{{hello}}", "Hello, ");
  t.add_tpl_string("{{world}}", "world!");

  std::string s = "{{hello}}{{world}}";

  t.parse(s);

  REQUIRE(s == "Hello, world!");
}

TEST_CASE("TPL: Hello, world!world!", "[tpl]") {

  TPL::TPL t;
  t.add_tpl_string("{{hello}}", "Hello, {{world}}");
  t.add_tpl_string("{{world}}", "world!");

  std::string s = "{{hello}}{{world}}";

  t.parse(s);

  REQUIRE(s == "Hello, world!world!");
}
