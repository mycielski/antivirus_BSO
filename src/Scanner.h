//
// Created by tomek on 3/22/22.
//

#ifndef ANTIVIRUS_BSO_SCANNER_H
#define ANTIVIRUS_BSO_SCANNER_H


#include <string>

enum HashType {
    MD5, SHA1, SHA256,
};

class Scanner {
public:
    Scanner(std::string path, std::string hashbase, HashType hashType);
    int scan();

private:
    std::string path;
    std::string hashbase;
    HashType hashType;
};


#endif //ANTIVIRUS_BSO_SCANNER_H
