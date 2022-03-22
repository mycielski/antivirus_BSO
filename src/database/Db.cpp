//
// Created by tomek on 3/22/22.
//

#include <fstream>
#include <iostream>
#include "Db.h"

std::vector<std::string> Db::loadHashes(std::string &path) {
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

bool Db::checkHash(std::string hash) {
    for (auto &h: hashes) {
        if (h == hash) {
            return true;
        }
    }

    return false;
}

Db::Db(std::string path) {
    this->hashes = loadHashes(path);

}

