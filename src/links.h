//
// Created by peeweep on 2020-03-06.
//

#ifndef SUPERSM_LINKS_H
#define SUPERSM_LINKS_H

#include <boost/filesystem.hpp>
#include <iostream>

namespace fs = boost::filesystem;

class links {
 public:
  links(std::vector<fs::path> v_source_directory, fs::path target_directory) {
    this->v_source_directory = v_source_directory;
    this->target_directory   = target_directory;
  }

  void links_all_files(fs::path        source_directory,
                       const fs::path& source_directory_saved) {
    for (auto& iter : fs::directory_iterator(source_directory)) {
      if (fs::is_directory(iter)) {
        links_all_files(iter, source_directory_saved);
      } else {
        // iter is source_file_path
        // target_directory: ~/target_directory
        // source_file_path: ~/source_directory/folder1/file1
        // get the right path: /folder1/file1
        // after split: ~/b/folder1/file1
        auto symlink_file =
            fs::path(this->target_directory.string() +
                     std::string(iter.path().string())
                         .erase(0, source_directory_saved.string().size()));

        // create parent directory if not exist
        if (!fs::exists(symlink_file.parent_path()))
          fs::create_directories(symlink_file.parent_path());

        // remove old file, create new symlink
        if (fs::exists(symlink_file) or fs::is_symlink(symlink_file)) {
          fs::remove(symlink_file);
        }
        fs::create_symlink(iter, symlink_file);

        std::cout << "ln -sf " << iter << " " << symlink_file << std::endl;
      }
    }
  }

  void add_links() {
    for (auto& it : this->v_source_directory) {
      if (!fs::is_directory(it)) {
        std::cerr << "Project " << it << " does not exist!\n";
        exit(1);
      }
      fs::path source_directory = fs::absolute(it);
      links_all_files(source_directory, source_directory);
    }
  }

  void del_all_links(fs::path        source_directory,
                     const fs::path& source_directory_saved) {
    for (auto& iter : fs::directory_iterator(source_directory)) {
      if (fs::is_directory(iter)) {
        del_all_links(iter, source_directory_saved);
      } else {
        // iter is source_file_path
        // target_directory: ~/target_directory
        // source_file_path: ~/source_directory/folder1/file1
        // get the right path: /folder1/file1
        // after split: ~/b/folder1/file1
        auto symlink_file =
            fs::path(this->target_directory.string() +
                     std::string(iter.path().string())
                         .erase(0, source_directory_saved.string().size()));
        // remove file if already exist, and it isn't a folder
        if (fs::is_symlink(symlink_file) or
            (!fs::is_directory(symlink_file) and fs::exists(symlink_file))) {
          fs::remove(symlink_file);
          std::cout << "delete symlink " << symlink_file << std::endl;
        } else {
          std::cout << symlink_file << "is not a file, skip" << std::endl;
        }
      }
    }
  }

  void del_links() {
    for (auto& it : this->v_source_directory) {
      if (!fs::is_directory(it)) {
        std::cerr << "Project " << it << " does not exist!\n";
        exit(1);
      }
      fs::path source_directory = fs::absolute(it);
      del_all_links(source_directory, source_directory);
    }
  }

 private:
  std::vector<fs::path> v_source_directory;
  fs::path              target_directory;
};

#endif  // SUPERSM_LINKS_H
