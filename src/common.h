//
// Created by peeweep on 2019-12-18.
//

#ifndef SUPERSM_COMMON_H
#define SUPERSM_COMMON_H

#define VERSION 0.4;

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <iostream>

#include "file.h"
class common {
 public:
  static void print_help_and_exit(
      const boost::program_options::options_description& description) {
    std::cout << "Super Symlinks Manager. [supersm] Version " << VERSION;
    std::cout << std::endl;
    std::cout << description;
    exit(1);
  }

  static boost::program_options::variables_map process_options(
      int argc, char const* argv[]) {
    // add options
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()("version,v", "version message")("help,h",
                                                       "help message")(
        "supersm,s",
        boost::program_options::value<std::vector<boost::filesystem::path>>()
            ->multitoken(),
        "supersm project")(
        "undo,u",
        boost::program_options::value<std::vector<boost::filesystem::path>>()
            ->multitoken(),
        "undo supersm")(
        "target,t",
        boost::program_options::value<boost::filesystem::path>()->default_value(
            boost::filesystem::current_path().parent_path()),
        "set target");

    // store map
    boost::program_options::variables_map variablesMap;

    // set as supersm if no options
    boost::program_options::positional_options_description p;
    p.add("supersm", -1);
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
    if (variablesMap.count("help") or argc <= 1
        //    or variablesMap["supersm"].empty()
    )
      print_help_and_exit(desc);

    boost::filesystem::path target_abs_path = boost::filesystem::absolute(
        variablesMap["target"].as<boost::filesystem::path>());

    if (!variablesMap["supersm"].empty())
      // range loop supersm project
      for (auto& it :
           variablesMap["supersm"].as<std::vector<boost::filesystem::path>>()) {
        const boost::filesystem::path& project_path = it;
        if (!boost::filesystem::is_directory(project_path)) {
          std::cout << "supersm project " << project_path << " Don't Exist!"
                    << std::endl;
          exit(1);
        }
        boost::filesystem::path project_abs_path =
            boost::filesystem::absolute(project_path);
        file::symlink_all_files(project_abs_path,
                                project_abs_path.string() + "/",
                                target_abs_path.string());
      }

    if (!variablesMap["undo"].empty())
      // range loop remove supersm project
      for (auto& it :
           variablesMap["undo"].as<std::vector<boost::filesystem::path>>()) {
        boost::filesystem::path project_abs_path =
            boost::filesystem::absolute(it);
        file::remove_all_symlinks(project_abs_path,
                                  project_abs_path.string() + "/",
                                  target_abs_path.string());
      }

    return variablesMap;
  }
};

#endif  // SUPERSM_COMMON_H
