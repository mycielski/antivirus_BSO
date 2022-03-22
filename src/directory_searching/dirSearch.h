//
// Created by tomek on 3/22/22.
//

#ifndef ANTIVIRUS_BSO_DIRSEARCH_H
#define ANTIVIRUS_BSO_DIRSEARCH_H

#include <string>
#include <list>
#include "../file/file.h"

std::list<File> dirSearch(std::string path);

#endif //ANTIVIRUS_BSO_DIRSEARCH_H
