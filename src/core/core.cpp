#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>
#define VERSION 0.1

void printFile(const std::filesystem::path &path) {
  for (auto &it : std::filesystem::directory_iterator(path)) {
    if (std::filesystem::is_directory(it))
      printFile(it);
    else
      std::cout << std::filesystem::path(it).string() << std::endl;
  }
}

void print_help_and_exit(
    boost::program_options::options_description description) {
  std::cout << "Super Symlinks Manager. [SuperSM] Version " << VERSION
            << std::endl;
  std::cout << description;
  exit(1);
}

int main(int argc, char const *argv[]) {
  std::string default_target = "DIR";

  // add options
  boost::program_options::options_description desc("Allowed options");
  desc.add_options()("version,v", "version message")("help,h", "help message")(
      "target,t",
      boost::program_options::value<std::filesystem::path>()->default_value(
          default_target),
      "set target");

  // store map
  boost::program_options::variables_map variablesMap;
  boost::program_options::store(
      boost::program_options::parse_command_line(argc, argv, desc),
      variablesMap);
  boost::program_options::notify(variablesMap);

  // set as target if no options
  boost::program_options::positional_options_description p;
  p.add("target", -1);
  boost::program_options::store(
      boost::program_options::command_line_parser(argc, argv)
          .options(desc)
          .positional(p)
          .run(),
      variablesMap);

  // print version and exit
  if (variablesMap.count("version")) {
    std::cout << VERSION << std::endl;
    exit(1);
  }

  // print help and exit
  if (variablesMap.count("help") or argc <= 1)
    print_help_and_exit(desc);

  // print target and exit
  if (variablesMap["target"].as<std::filesystem::path>().string() !=
      default_target) {
    std::cout << "Target was set to "
              << variablesMap["target"].as<std::filesystem::path>()
              << std::endl;
    exit(1);
  }

  return 0;
}
