//
// Created by tomek on 3/22/22.
//

#ifndef ANTIVIRUS_BSO_SCANNER_H
#define ANTIVIRUS_BSO_SCANNER_H

#include <list>
#include <string>

#include "database/db.h"
#include "file/file.h"

enum HashType {
  MD5,
  SHA1,
  SHA256,
};

class scanner {
 public:
  scanner(std::string path, std::string databasePath, HashType hashType);
  int Scan();

  void SetPath(const std::string &path);

  void SetDatabase(const db &database);

  void SetHashType(HashType hashType);

 private:
  std::string path;
  db database;
  HashType hash_type;

  static std::__cxx11::list<File> DirSearch(std::string &path);
};

#endif  // ANTIVIRUS_BSO_SCANNER_H
