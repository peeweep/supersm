//
// Created by peeweep on 2019-12-21.
//

#ifndef SUPERSM_FILE_H
#define SUPERSM_FILE_H

#include <filesystem>
#include <iostream>

class file {
public:
  static std::string split_path(std::string source,
                                std::string project_split_string) {
    return source.erase(0, project_split_string.size());
  }

  static void create_dir_if_not_exist(std::filesystem::path path) {
    if (!std::filesystem::exists(path))
      std::filesystem::create_directories(path);
  }

  static void remove_file_if_already_exist(std::filesystem::path path) {
    if (std::filesystem::exists(path))
      std::filesystem::remove(path);
  }

  static void symlink_all_files(const std::filesystem::path &project,
                                const std::string &project_split_string,
                                const std::string &target_string) {
    for (auto &iter : std::filesystem::directory_iterator(project))
      if (std::filesystem::is_directory(iter))
        symlink_all_files(iter, project_split_string, target_string);
      else {
        std::filesystem::path symlink_path =
            std::filesystem::path(target_string) /
            std::filesystem::path(
                split_path(iter.path().string(), project_split_string));
        create_dir_if_not_exist(symlink_path.parent_path());
        remove_file_if_already_exist(symlink_path);
        std::filesystem::create_symlink(iter, symlink_path);
        std::cout << "ln -sf " << iter.path() << " " << symlink_path
                  << std::endl;
      }
  }

  static void remove_all_symlinks(const std::filesystem::path &project,
                                  const std::string &project_split_string,
                                  const std::string &target_string) {
    for (auto &iter : std::filesystem::directory_iterator(project))
      if (std::filesystem::is_directory(iter))
        remove_all_symlinks(iter, project_split_string, target_string);
      else {
        std::filesystem::path symlink_path =
            std::filesystem::path(target_string) /
            std::filesystem::path(
                split_path(iter.path().string(), project_split_string));

        if (!std::filesystem::exists(symlink_path)) {
          std::cout << symlink_path << " don't exist!" << std::endl;
          exit(1);
        }

        if (std::filesystem::read_symlink(symlink_path).string() !=
            iter.path()) {
          std::cout << symlink_path
                    << " already is a symlink but not the same as "
                    << std::filesystem::read_symlink(symlink_path).string()
                    << std::endl;
          exit(1);
        }
        std::filesystem::remove(symlink_path);
      }
  }
};

#endif // SUPERSM_FILE_H
