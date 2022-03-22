//
// Created by tomek on 3/22/22.
//

#include "dirSearch.h"
#include <filesystem>

namespace fs = std::filesystem;

std::list<File> dirSearch(std::string& path) {
    std::list<File> files;
    for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.emplace_back(File(entry.path().string()));
        }
    }
    return files;
}

