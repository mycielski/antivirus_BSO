//
// Created by tomek on 3/22/22.
//

#include "db.h"

#include <fstream>
#include <iostream>

std::vector<std::string> db::LoadHashes(std::string &path) {
  std::vector<std::string> hashes;
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("File does not exist");
  }
  std::string line;
  while (std::getline(file, line)) {
    hashes.push_back(line);
  }
  return hashes;
}

bool db::CheckHash(std::string hash) {
  for (auto &h : hashes) {
    if (h == hash) {
      return true;
    }
  }

  return false;
}

db::db(std::string path) { this->hashes = LoadHashes(path); }
