#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <string>

#include <manifesto.hpp>

std::string test_string = R"~(
project: TestProject
version: 0.1.0
author: Jeffrey "The Dude" Lebowski
contributors:
  - Walter Sobchak
  - Theodore Donald "Donny" Kerabatsos
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

  auto contrib = kv.subtree("contributors");

  REQUIRE(contrib[1][1] == "Walter Sobchak");
  REQUIRE(contrib[2][1] == "Theodore Donald \"Donny\" Kerabatsos");

  REQUIRE(kv["build"][1] == "cmake");
  REQUIRE(kv["ci"][1] == "travis");
  REQUIRE(kv["structure"][1] == "gnu");

  auto deps = kv.subtree("dependencies");

  REQUIRE(deps["something"][1] == "hash");
  REQUIRE(deps["somethingelse"][1] == "0.1.2");
  REQUIRE(deps["somethingelseentirely"][1] == "http://git.com");
}

TEST_CASE("Manifesto: Emitter", "[manifesto]") {
  Manifesto::Parser pr;
  Manifesto::Emitter em;

  Manifesto::Manifest m;

  m.add_entry("project", "TestProject", KVIL0);
  m.add_entry("version", "0.1.0", KVIL0);
  m.add_entry("author", "Jeffrey \"The Dude\" Lebowski", KVIL0);
  m.add_entry("contributors", "", KVIL0);
  m.add_entry("", "Walter Sobchak", KVIL1);
  m.add_entry("", "Theodore Donald \"Donny\" Kerabatsos", KVIL1);
  m.add_entry("build", "cmake", KVIL0);
  m.add_entry("ci", "travis", KVIL0);
  m.add_entry("structure", "gnu", KVIL0);
  m.add_entry("dependencies", "", KVIL0);
  m.add_entry("something", "hash", KVIL1);
  m.add_entry("somethingelse", "0.1.2", KVIL1);
  m.add_entry("somethingelseentirely", "http://git.com", KVIL1);

  auto kv = m.get_kvistore();
  std::string s = em.emit(kv);

  auto kv_test = pr.parse(test_string);
  std::string t = em.emit(kv_test);

  REQUIRE(s == t);
}

TEST_CASE("Manifesto: Read/Write", "[manifesto]") {
  Manifesto::Emitter em;

  Manifesto::Manifest m1;

  m1.add_entry("project", "TestProject", KVIL0);
  m1.add_entry("version", "0.1.0", KVIL0);
  m1.add_entry("author", "Jeffrey \"The Dude\" Lebowski", KVIL0);
  m1.add_entry("contributors", "", KVIL0);
  m1.add_entry("", "Walter Sobchak", KVIL1);
  m1.add_entry("", "Theodore Donald \"Donny\" Kerabatsos", KVIL1);
  m1.add_entry("build", "cmake", KVIL0);
  m1.add_entry("ci", "travis", KVIL0);
  m1.add_entry("structure", "gnu", KVIL0);
  m1.add_entry("dependencies", "", KVIL0);
  m1.add_entry("something", "hash", KVIL1);
  m1.add_entry("somethingelse", "0.1.2", KVIL1);
  m1.add_entry("somethingelseentirely", "http://git.com", KVIL1);

  m1.write_manifest("./test_manifest.yaml");

  Manifesto::Manifest m2;

  m2.read_manifest("./test_manifest.yaml");

  auto kv1 = m1.get_kvistore();
  std::string s1 = em.emit(kv1);

  auto kv2 = m2.get_kvistore();
  std::string s2 = em.emit(kv2);

  REQUIRE(s1 == s2);
}
