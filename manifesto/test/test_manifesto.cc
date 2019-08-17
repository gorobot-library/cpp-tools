#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include <manifesto.hpp>

std::string test_string = R"~(
project: TestProject
version: 0.1.0
author: Jeffrey "The Dude" Lebowski

build: cmake
ci   : travis

structure: gnu

dependencies:
  - something            : hash
  - somethingelse        : 0.1.2
  - somethingelseentirely: http://git.com
)~";

TEST_CASE("Manifesto: Parser", "[manifesto]") {
  Manifesto::Parser pr;

  auto kv = pr.parse(test_string);

  REQUIRE(kv["project"][1] == "TestProject");
  REQUIRE(kv["version"][1] == "0.1.0");
  REQUIRE(kv["author"][1] == "Jeffrey \"The Dude\" Lebowski");
  REQUIRE(kv["build"][1] == "cmake");
  REQUIRE(kv["ci"][1] == "travis");

  auto sub = kv.subtree("dependencies");

  REQUIRE(kv["something"][1] == "hash");
  REQUIRE(kv["somethingelse"][1] == "0.1.2");
  REQUIRE(kv["somethingelseentirely"][1] == "http://git.com");
}

TEST_CASE("Manifesto: Emitter", "[manifesto]") {
  Manifesto::Emitter em;

  Manifesto::KVITuple kt;
  Manifesto::KVIStore kv;

  kt = {"project", "TestProject", ""};
  kv.emplace_back(kt);
  kt = {"dependencies", "", ""};
  kv.emplace_back(kt);
  kt = {"something", "hash", "  "};
  kv.emplace_back(kt);

  std::string s = em.emit(kv);

  std::cout << s;
}
