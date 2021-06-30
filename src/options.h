//
// Created by peeweep on 2020-03-06.
//

#ifndef SUPERSM_OPTIONS_H
#define SUPERSM_OPTIONS_H
#define SUPERSM_VERSION_MAJOR 0
#define SUPERSM_VERSION_MINOR 5
#define SUPERSM_VERSION_REVISION 2

#define SUPERSM_AUX_STR_EXP(__A) #__A
#define SUPERSM_AUX_STR(__A) SUPERSM_AUX_STR_EXP(__A)

#define SUPERSM_VERSION_STR              \
  SUPERSM_AUX_STR(SUPERSM_VERSION_MAJOR) \
  "." SUPERSM_AUX_STR(SUPERSM_VERSION_MINOR) "." SUPERSM_AUX_STR(SUPERSM_VERSION_REVISION) " "

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

#include "links.h"

namespace fs = boost::filesystem;
namespace po = boost::program_options;

class options {
 public:
  static void parse_option(int argc, char const* argv[]) {
    // add options
    po::options_description desc("Allowed options");
    desc.add_options()
        // version message
        ("version,V", "version message")
        // help message
        ("help,H", "help message")
        // target option's default value is current_path's parent_path
        ("target,T",
         po::value<fs::path>()->default_value(fs::current_path().parent_path()),
         "set target")
        // Add links
        ("add,A", po::value<std::vector<fs::path>>()->multitoken(), "Add links")
        // Remove links
        ("delete,D", po::value<std::vector<fs::path>>()->multitoken(),
         "Remove links");

    // store map
    po::variables_map variablesMap;
    // set as supersm if no options
    boost::program_options::positional_options_description p;
    p.add("add", -1);
    po::store(po::command_line_parser(argc, argv)
                  .options(desc)
                  .allow_unregistered()
                  .positional(p)
                  .run(),
              variablesMap);
    po::notify(variablesMap);

    // Convert "target" option's value to absolute path
    fs::path target = fs::absolute(variablesMap["target"].as<fs::path>());

    // print version message
    if (!variablesMap["version"].empty()) {
      std::cout << SUPERSM_VERSION_STR << std::endl;
      exit(1);
    }
    // print help
    if (!variablesMap["help"].empty() or argc <= 1) {
      std::cout << "Super Symlinks Manager.";
      std::cout << "[supersm] Version " << SUPERSM_VERSION_STR << std::endl;
      std::cout << desc;
      exit(1);
    }
    // Add links
    if (!variablesMap["add"].empty()) {
      auto link =
          links(variablesMap["add"].as<std::vector<fs::path>>(), target);
      link.add_links();
    }
    // remove links
    if (!variablesMap["delete"].empty()) {
      auto link =
          links(variablesMap["delete"].as<std::vector<fs::path>>(), target);
      link.del_links();
    }
  }
};

#endif  // SUPERSM_COMMON_H
