//
// Created by tomek on 3/22/22.
//

#include "Scanner.h"
#include "directory_searching/dirSearch.h"

#include <utility>

Scanner::Scanner(std::string path, std::string hashbase, HashType hashType) : path(std::move(path)),
                                                                                            hashbase(std::move(hashbase)),
                                                                                            hashType(hashType) {}

int Scanner::scan() {
    if (path.empty()) {
        perror("Empty path");
        return -1;
    }
    auto files = dirSearch(path);

    for (auto file : files){

    }
    return 0;
}
