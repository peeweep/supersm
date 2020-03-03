//
// Created by peeweep on 2019-12-21.
//

#ifndef SUPERSM_FILE_H
#define SUPERSM_FILE_H

#include <boost/filesystem.hpp>
#include <iostream>

class file {
 public:
  static std::string split_path(std::string source,
                                std::string project_split_string) {
    return source.erase(0, project_split_string.size());
  }

  static void create_dir_if_not_exist(boost::filesystem::path path) {
    if ((boost::filesystem::exists(path) and
         !boost::filesystem::is_directory(path)) or
        boost::filesystem::is_symlink(path)) {
      std::cout << path << " is a file, delete it and create folder"
                << std::endl;
      boost::filesystem::remove(path);
      boost::filesystem::create_directories(path);
    } else if (!boost::filesystem::exists(path)) {
      std::cout << path << " does not exist, create it" << std::endl;
      boost::filesystem::create_directories(path);
    }
  }

  static void remove_file_if_already_exist(boost::filesystem::path path) {
    if (boost::filesystem::exists(path) or boost::filesystem::is_symlink(path))
      boost::filesystem::remove(path);
  }

  static void symlink_all_files(const boost::filesystem::path &project,
                                const std::string &project_split_string,
                                const std::string &target_string) {
    for (auto &iter : boost::filesystem::directory_iterator(project))
      if (boost::filesystem::is_directory(iter))
        symlink_all_files(iter, project_split_string, target_string);
      else {
        boost::filesystem::path symlink_path =
            boost::filesystem::path(target_string) /
            boost::filesystem::path(
                split_path(iter.path().string(), project_split_string));
        create_dir_if_not_exist(symlink_path.parent_path());
        remove_file_if_already_exist(symlink_path);
        boost::filesystem::create_symlink(iter, symlink_path);
        std::cout << "ln -sf " << iter.path() << " " << symlink_path
                  << std::endl;
      }
  }

  static void is_symlink_path_exist(const boost::filesystem::path &symlink_path,
                                    bool &run_next_loop) {
    if (!boost::filesystem::is_symlink(symlink_path)) {
      std::string type;
      std::cout
          << symlink_path
          << " is not a symlink! Are you sure continue run next loop? Y/N? "
             "(default:Y) ";
      std::getline(std::cin, type);
      if (type == "y" or type == "Y" or type.empty()) {
        run_next_loop = true;
        return;
      } else if (type == "n" or type == "N") {
        std::cout << "Let's Quit" << std::endl;
        exit(1);
      } else {
        std::cout << "wrong value, please re-type" << std::endl;
        is_symlink_path_exist(symlink_path, run_next_loop);
      }
    }
  }

  static void remove_all_symlinks(const boost::filesystem::path &project,
                                  const std::string &project_split_string,
                                  const std::string &target_string) {
    for (auto &iter : boost::filesystem::directory_iterator(project))
      if (boost::filesystem::is_directory(iter))
        remove_all_symlinks(iter, project_split_string, target_string);
      else {
        boost::filesystem::path symlink_path =
            boost::filesystem::path(target_string) /
            boost::filesystem::path(
                split_path(iter.path().string(), project_split_string));

        bool run_next_loop = false;
        is_symlink_path_exist(symlink_path, run_next_loop);
        if (run_next_loop)
          continue;

        if (boost::filesystem::read_symlink(symlink_path).string() !=
            iter.path()) {
          std::cout << symlink_path
                    << " already is a symlink but not the same as "
                    << boost::filesystem::read_symlink(symlink_path).string()
                    << std::endl;
          exit(1);
        }
        boost::filesystem::remove(symlink_path);
        std::cout << "Delete symlink: " << iter.path() << std::endl;
      }
  }
};

#endif  // SUPERSM_FILE_H
