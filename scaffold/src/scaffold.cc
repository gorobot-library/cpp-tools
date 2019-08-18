#include <iostream>

#include <clap.hpp>

#include "../lib/scaffold.hpp"

int main (int argc, char *argv[]) {


  Scaffold::Scaffold scaf("TestProject");
  scaf.create_directory("./test");
  scaf.generate_cmake("./CMakeLists.txt");
  // Scaffold::create_directory("./bin");
  // Scaffold::create_directory("./build");
  // Scaffold::create_directory("./include");
  // Scaffold::create_directory("./lib");
  // Scaffold::create_directory("./src");

  // CLAP::CLAP args;
  //
  // args.add_option("-v", false, "Display version.");
  // args.add_option("-h", false, "Display help.");
  //
  // args.parse(argc, argv);
  //
  // bool val = args.get_value<bool>("-v");
  //
  // std::cout << val << '\n';

  return 0;
}
