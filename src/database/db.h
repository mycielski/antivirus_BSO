//
// Created by tomek on 3/22/22.
//

#ifndef ANTIVIRUS_BSO_DB_H
#define ANTIVIRUS_BSO_DB_H


#include <string>
#include <vector>

class db {
public:
    db(const std::string &path);

private:
    std::string path;
    std::vector<std::string> hashes;

};


#endif //ANTIVIRUS_BSO_DB_H
