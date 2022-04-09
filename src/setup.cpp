//
// Created by tomek on 4/9/22.
//

#include "setup.h"

#include <filesystem>

bool check_if_quarantine_dir_exists() {
    if (std::filesystem::exists(QUARANTINE_DIRECTORY) && std::filesystem::is_directory(QUARANTINE_DIRECTORY))
        return true;
    return false;
}

int create_quarantine_dir() {
    if (check_if_quarantine_dir_exists())
        return 0;
    if (std::filesystem::create_directory(QUARANTINE_DIRECTORY))
        return 0;
    return -1;
}