//
// Created by tomek on 3/22/22.
//

#ifndef ANTIVIRUS_BSO_DB_H
#define ANTIVIRUS_BSO_DB_H


#include <string>
#include <vector>

class Db {
public:
    Db(std::string path);

    bool checkHash(std::string hash);

private:
    std::vector<std::string> hashes;
    std::vector<std::string> loadHashes(std::string& path);
};


#endif //ANTIVIRUS_BSO_DB_H
