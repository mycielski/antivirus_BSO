//
// Created by tomek on 3/22/22.
//

#ifndef ANTIVIRUS_BSO_SCANNER_H
#define ANTIVIRUS_BSO_SCANNER_H


#include <string>
#include <list>
#include "database/Db.h"
#include "file/file.h"

enum HashType {
    MD5, SHA1, SHA256,
};

class Scanner {
public:
    Scanner(std::string path, std::string databasePath, HashType hashType);
    int scan();

private:
    std::string path;
    Db database;
    HashType hashType;

    static std::__cxx11::list<File> dirSearch(std::string &path);
};


#endif //ANTIVIRUS_BSO_SCANNER_H
