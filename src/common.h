//
// Created by peeweep on 2019-12-18.
//

#ifndef SUPERSM_COMMON_H
#define SUPERSM_COMMON_H

#define VERSION 0.1;

#include <boost/program_options.hpp>
#include <filesystem>
#include <iostream>

#include "file.h"
class common {
 public:
  static void print_help_and_exit(
      const boost::program_options::options_description& description) {
    std::cout << "Super Symlinks Manager. [SuperSM] Version " << VERSION;
    std::cout << std::endl;
    std::cout << description;
    exit(1);
  }

  static boost::program_options::variables_map process_options(
      int argc, char const* argv[]) {
    // add options
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()("version,v", "version message")(
        "SuperSM,s",
        boost::program_options::value<std::filesystem::path>()
        //            ->default_value(
        //            std::filesystem::path("/home/peeweep/fcitx5"))
        ,
        "SuperSM project")("help,h", "help message")(
        "target,t",
        boost::program_options::value<std::filesystem::path>()->default_value(
            std::filesystem::current_path().parent_path()),
        "set target");

    // store map
    boost::program_options::variables_map variablesMap;

    // set as SuperSM if no options
    boost::program_options::positional_options_description p;
    p.add("SuperSM", -1);
    boost::program_options::store(
        boost::program_options::command_line_parser(argc, argv)
            .options(desc)
            .allow_unregistered()
            .positional(p)
            .run(),
        variablesMap);
    boost::program_options::notify(variablesMap);

    // print version and exit
    if (variablesMap.count("version")) {
      std::cout << VERSION;
      std::cout << std::endl;
      exit(1);
    }

    // print help and exit
    if (variablesMap.count("help") or argc <= 1 or
        variablesMap["SuperSM"].empty())
      print_help_and_exit(desc);

    // print SuperSM project
    std::filesystem::path project_path =
        variablesMap["SuperSM"].as<std::filesystem::path>();
    bool supersm_project_exist = std::filesystem::is_directory(project_path);

    if (supersm_project_exist) {
      std::cout << "SuperSM project was set to " << project_path << std::endl;
    } else {
      std::cout << "SuperSM project " << project_path << " Don't Exist!"
                << std::endl;
      exit(1);
    }
    std::filesystem::path project_abs_path =
        std::filesystem::absolute(project_path);

    std::filesystem::path target_abs_path = std::filesystem::absolute(
        variablesMap["target"].as<std::filesystem::path>());

    file::print_all_files(project_abs_path, project_abs_path.string() + "/",
                          target_abs_path.string());

    return variablesMap;
  }

 private:
};

#endif  // SUPERSM_COMMON_H
