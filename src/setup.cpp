//
// Created by tomek on 4/9/22.
//

#include "setup.h"

#include <filesystem>

bool CheckIfQuarantineDirExists() {
  if (std::filesystem::exists(kQuarantineDirectory) &&
      std::filesystem::is_directory(kQuarantineDirectory))
    return true;
  return false;
}

int CreateQuarantineDir() {
  if (CheckIfQuarantineDirExists()) return 0;
  if (std::filesystem::create_directory(kQuarantineDirectory)) return 0;
  return -1;
}