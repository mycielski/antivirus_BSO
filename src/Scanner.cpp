//
// Created by tomek on 3/22/22.
//

#include "Scanner.h"
#include "database/Db.h"
#include "file/file.h"

#include <utility>
#include <iostream>
#include <list>
#include <filesystem>

namespace fs = std::filesystem;


Scanner::Scanner(std::string path, std::string dbPath, HashType hashType) : database(dbPath){
    this->path = path;
    this->hashType = hashType;
}

std::list<File> Scanner::dirSearch(std::string& path) {
    std::list<File> files;
    for (const fs::directory_entry& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.emplace_back(File(entry.path().string()));
        }
    }
    return files;
}


int Scanner::scan() {
    if (path.empty()) {
        perror("Empty path");
        return -1;
    }
    auto files = dirSearch(path);
    for (auto file : files){
        file.setMalicious(database.checkHash(file.getSha256()));
        if (file.isMalicious()) {
            std::cout << file.getPath() << " is malicious. Its hash is: " << file.getSha256() << std::endl;
        }
    }
    return 0;
}



