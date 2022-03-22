//
// Created by tomek on 3/22/22.
//

#include "file.h"
#include "../hash/sha256.h"

File::File(const std::string &path) : path(path) {
    this -> path = path;
    this -> sha256 = fileSha256(path);
}

const std::string &File::getSha256() const {
    return sha256;
}

void File::setMalicious(bool malicious) {
    File::malicious = malicious;
}

bool File::isMalicious() const {
    return malicious;
}

const std::string &File::getPath() const {
    return path;
}

