//
// Created by tomek on 3/22/22.
//

#include "scanner.h"

#include <sys/stat.h>

#include <filesystem>
#include <iostream>
#include <list>
#include <regex>
#include <utility>

#include "database/db.h"
#include "file/file.h"
#include "setup.h"

namespace fs = std::filesystem;

scanner::scanner(std::string path, std::string dbPath, HashType hashType)
    : database(dbPath) {
  this->path = std::move(path);
  this->hash_type = hashType;
}

std::list<File> scanner::DirSearch(std::string &path) {
  // convert path to absolute if it is not already absolute
  if (path.front() != '/') {
    path = fs::absolute(path).string();
  }
  std::list<File> files;
  for (const fs::directory_entry &entry :
       fs::recursive_directory_iterator(path)) {
    try {
      if (fs::is_symlink(entry.path()) or
          entry.path() == std::string("/swapfile") or
          entry.path().string().substr(0, 5) == std::string("/proc") or
          entry.path().string().substr(0, 4) == std::string("/dev/")) {
        continue;
      } else if (entry.is_regular_file()) {
        files.emplace_back(File(entry.path().string()));
        std::cout << std::flush << "\rScanning " << files.size()
                  << " files... ";
      }
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  std::cout << "\nScan complete." << std::endl;
  return files;
}

std::string QuarantineInstanceSetup() {
  // create new directory with its name being the date
  auto t = std::time(nullptr);
  // create a string representation of the time in format YYYY-MM-DD--HH-MM-SS
  auto tm = *std::localtime(&t);
  std::stringstream ss;
  ss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
  std::string dirName = ss.str();
  std::string quarantinePath = kQuarantineDirectory + "/" + dirName;
  if (mkdir(quarantinePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) ==
      -1) {
    std::cerr << "Error creating quarantine directory" << std::endl;
    exit(EXIT_FAILURE);
  }
  //    // inside the directory create a log file
  //    std::string logPath = quarantinePath + "/log.txt";
  return quarantinePath += "/";
}

int scanner::Scan() {
  std::cout << "Creating quarantine directory for this Scan..." << std::endl;
  std::string quarantine_path = QuarantineInstanceSetup();
  std::cout << "Quarantine directory created at " << quarantine_path
            << std::endl;
  if (path.empty()) [[unlikely]] {
    perror("Empty path");
    exit(EXIT_FAILURE);
  } else if (fs::is_regular_file(path)) {
    std::cout << "Scanning file: " << path << std::endl;
    File file(path);
      file.SetMalicious(database.CheckHash(file.GetSha256()));
    if (not file.IsMalicious()) {
      std::cout << "File is not malicious" << std::endl;
      return 0;
    }
    std::cout << file.GetPath() << " is malicious. Its hash is "
              << file.GetSha256() << std::endl;
    std::cout << "Quarantining file... ";
    // create a symlink from discovered malicious file to this Scan's quarantine
    // directory
    if (symlink(file.GetPath().c_str(),
                (quarantine_path + file.GetSha256()).c_str()) == -1) {
      perror("Error creating symlink");
    }
    std::cout << "Done. " << std::endl;
    return 1;
  }
  auto files = DirSearch(path);
  int malicious_files = 0;
  for (auto file : files) {
      file.SetMalicious(database.CheckHash(file.GetSha256()));
    if (file.IsMalicious()) [[unlikely]] {
      std::cout << file.GetPath()
                << " is malicious. Its hash is: " << file.GetSha256()
                << std::endl;
      chmod(file.GetPath().c_str(), S_IRUSR | S_IRGRP | S_IROTH);
      std::cout << "Quarantining file... ";
      // create a symlink from discovered malicious file to this Scan's
      // quarantine directory
      if (symlink(file.GetPath().c_str(),
                  (quarantine_path + file.GetSha256()).c_str()) == -1) {
        perror("Error creating symlink");
      }
      std::cout << "Done. " << std::endl;
      malicious_files++;
    }
  }
  std::cout
      << "Scanning finished. " << malicious_files
      << " files are malicious. They were moved to the quarantine directory."
      << std::endl;
  return malicious_files;
}

void scanner::SetPath(const std::string &path) { scanner::path = path; }

void scanner::SetDatabase(const db &database) { scanner::database = database; }

void scanner::SetHashType(HashType hashType) { scanner::hash_type = hashType; }
