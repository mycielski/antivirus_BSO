//
// Created by tomek on 3/22/22.
//

#ifndef ANTIVIRUS_BSO_DB_H
#define ANTIVIRUS_BSO_DB_H

#include <string>
#include <vector>

class db {
 public:
  db(std::string path);

  bool CheckHash(std::string hash);

 private:
  std::vector<std::string> hashes;
  std::vector<std::string> LoadHashes(std::string& path);
};

#endif  // ANTIVIRUS_BSO_DB_H
