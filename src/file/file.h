//
// Created by tomek on 3/22/22.
//

#ifndef ANTIVIRUS_BSO_FILE_H
#define ANTIVIRUS_BSO_FILE_H


#include <string>

class File {
public:
    File(const std::string &path);

    const std::string &getSha256() const;

    void setMalicious(bool malicious);

    bool isMalicious() const;

    const std::string &getPath() const;

private:
    std::string path;
    std::string sha256;
    bool malicious;


};


#endif //ANTIVIRUS_BSO_FILE_H
