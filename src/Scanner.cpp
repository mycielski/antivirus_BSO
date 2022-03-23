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
#include <sys/stat.h>

namespace fs = std::filesystem;


Scanner::Scanner(std::string path, std::string dbPath, HashType hashType) : database(dbPath){
    this->path = path;
    this->hashType = hashType;
}

std::list<File> Scanner::dirSearch(std::string& path) {
    std::list<File> files;
    for (const fs::directory_entry& entry : fs::recursive_directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.emplace_back(File(entry.path().string()));
        }
    }
    return files;
}

//int chmod(const char *path, mode_t mode) {
//
//    return 0;
//}


int Scanner::scan() {
    if (path.empty()) {
        perror("Empty path");
        return -1;
    } else if (fs::is_regular_file(path)) {
        File file(path);
        file.setMalicious(database.checkHash(file.getSha256()));
        std::cout << file.getPath() << " is malicious. Its hash is " << file.getSha256() << std::endl;
        return 1;
    }
    auto files = dirSearch(path);
    int malicious_files = 0;
    for (auto file : files){
        file.setMalicious(database.checkHash(file.getSha256()));
        if (file.isMalicious()) {
            std::cout << file.getPath() << " is malicious. Its hash is: " << file.getSha256() << std::endl;
            chmod(file.getPath().c_str(), S_IRUSR | S_IRGRP | S_IROTH);
            malicious_files++;
        }
    }
    return malicious_files;
}

void Scanner::setPath(const std::string &path) {
    Scanner::path = path;
}

void Scanner::setDatabase(const Db &database) {
    Scanner::database = database;
}

void Scanner::setHashType(HashType hashType) {
    Scanner::hashType = hashType;
}



