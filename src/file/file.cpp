//
// Created by tomek on 3/22/22.
//

#include "file.h"
#include "../hash/sha256.h"

File::File(const std::string &path) : path(path) {
    this -> path = path;
    this -> sha256 = fileSha256(path);
}

