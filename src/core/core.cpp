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

int main(int argc, char const *argv[]) {
  boost::program_options::options_description desc("Allowed options");

  std::string default_target = "DIR";
  desc.add_options()("version,v", "version message")("help,h", "help message")(
      "target,t",
      boost::program_options::value<std::filesystem::path>()->default_value(
          default_target),
      "set target");

  boost::program_options::variables_map vm;
  boost::program_options::store(
      boost::program_options::parse_command_line(argc, argv, desc), vm);
  boost::program_options::notify(vm);

  if (vm.count("version")) {
    std::cout << VERSION << std::endl;
    return 1;
  } else {
    std::cout << "Super Symlinks Manager. [SuperSM] Version " << VERSION
              << std::endl;
    std::cout << desc << std::endl;
  }

  if (vm["target"].as<std::filesystem::path>().string() != default_target) {
    std::cout << "Target was set to "
              << vm["target"].as<std::filesystem::path>() << std::endl;
  }

  //  else
  //    std::cout << "Target was set to default" << std::endl;

  return 0;
}
