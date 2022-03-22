//
// Created by tomek on 3/22/22.
//

#include <fstream>
#include "db.h"

std::vector<std::string> loadHashes(std::string &path) {
    std::vector<std::string> hashes;
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        hashes.push_back(line);
    }
    return hashes;
}

bool lookupHash(std::string &hash, std::vector<std::string> &hashes) {
    for (auto &h: hashes)
        if (h == hash)
            return true;


    return false;
}

