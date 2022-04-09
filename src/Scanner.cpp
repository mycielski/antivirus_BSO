//
// Created by tomek on 3/22/22.
//

#include "Scanner.h"
#include "database/Db.h"
#include "file/file.h"
#include "setup.h"

#include <utility>
#include <iostream>
#include <list>
#include <filesystem>
#include <sys/stat.h>
#include <regex>

namespace fs = std::filesystem;


Scanner::Scanner(std::string path, std::string dbPath, HashType hashType) : database(dbPath) {
    this->path = std::move(path);
    this->hashType = hashType;
}

std::list<File> Scanner::dirSearch(std::string &path) {
    std::list<File> files;
    for (const fs::directory_entry &entry: fs::recursive_directory_iterator(path)) {
        if (entry.is_regular_file()) {
            files.emplace_back(File(entry.path().string()));
        } else if (std::regex_match(entry.path().string(), std::regex("^\\/proc"))) [[unlikely]] {
            continue;
        }
    }
    return files;
}


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
    std::cout << "File discovery." << std::endl;
    auto files = dirSearch(path);
    int malicious_files = 0;
    std::cout << "Scanning " << files.size() << " files..." << std::endl;
    for (auto file: files) {
        file.setMalicious(database.checkHash(file.getSha256()));
        if (file.isMalicious()) [[unlikely]] {
            std::cout << file.getPath() << " is malicious. Its hash is: " << file.getSha256() << std::endl;
            chmod(file.getPath().c_str(), S_IRUSR | S_IRGRP | S_IROTH);
            malicious_files++;
        }
    }
    std::cout << "Scanning finished. " << malicious_files << " files are malicious." << std::endl;
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



