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
#include <semaphore>

namespace fs = std::filesystem;


Scanner::Scanner(std::string path, std::string dbPath, HashType hashType) : database(dbPath) {
    this->path = std::move(path);
    this->hashType = hashType;
}

std::list<File> Scanner::dirSearch(std::string &path) {
    std::cout << "File discovery... " << std::endl;
    std::list<File> files;
    for (const fs::directory_entry &entry: fs::recursive_directory_iterator(path)) {
        if (entry.is_regular_file()) {
            try { files.emplace_back(File(entry.path().string())); } catch (std::exception &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
    std::cout << "Done." << std::endl;
    return files;
}

std::string quarantine_instance_setup() {
    // create new directory with its name bein the date
    auto t = std::time(nullptr);
    // create a string representation of the time in format YYYY-MM-DD--HH-MM-SS
    auto tm = *std::localtime(&t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    std::string dirName = ss.str();
    std::string quarantinePath = QUARANTINE_DIRECTORY + "/" + dirName;
    if (mkdir(quarantinePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
        std::cerr << "Error creating quarantine directory" << std::endl;
        exit(EXIT_FAILURE);
    }
//    // inside the directory create a log file
//    std::string logPath = quarantinePath + "/log.txt";
    return quarantinePath += "/";
}

int Scanner::scan() {
    std::cout << "Creating quarantine directory for this scan..." << std::endl;
    std::string quarantine_path = quarantine_instance_setup();
    std::cout << "Quarantine directory created at " << QUARANTINE_DIRECTORY + quarantine_path << std::endl;
    if (path.empty()) [[unlikely]] {
        perror("Empty path");
        exit(EXIT_FAILURE);
    } else if (fs::is_regular_file(path)) {
        std::cout << "Scanning file: " << path << std::endl;
        File file(path);
        file.setMalicious(database.checkHash(file.getSha256()));
        if (not file.isMalicious()) {
            std::cout << "File is not malicious" << std::endl;
            return 0;
        }
        std::cout << file.getPath() << " is malicious. Its hash is " << file.getSha256() << std::endl;
        std::cout << "Quarantining file... ";
        // create a symlink from discovered malicious file to this scan's quarantine directory
        if (symlink(file.getPath().c_str(), (quarantine_path + file.getSha256()).c_str()) == -1) {
            perror("Error creating symlink");
            exit(EXIT_FAILURE);
        }
        std::cout << "Done. " << std::endl;
        return 1;
    }
    auto files = dirSearch(path);
    int malicious_files = 0;
    std::cout << "Scanning " << files.size() << " files..." << std::endl;
    for (auto file: files) {
        std::cout << "Scanning " << file.getPath() << "..." << std::endl;
        file.setMalicious(database.checkHash(file.getSha256()));
        if (file.isMalicious()) [[unlikely]] {
            std::cout << file.getPath() << " is malicious. Its hash is: " << file.getSha256() << std::endl;
            chmod(file.getPath().c_str(), S_IRUSR | S_IRGRP | S_IROTH);
            std::cout << "Quarantining file... ";
            // create a symlink from discovered malicious file to this scan's quarantine directory
            if (symlink(file.getPath().c_str(), (quarantine_path + file.getSha256()).c_str()) == -1) {
                perror("Error creating symlink");
                exit(EXIT_FAILURE);
            }
            std::cout << "Done. " << std::endl;
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



