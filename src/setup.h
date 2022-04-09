//
// Created by tomek on 4/9/22.
//

#ifndef ANTIVIRUS_BSO_SETUP_H
#define ANTIVIRUS_BSO_SETUP_H

#include <string>

const std::string QUARANTINE_DIRECTORY = "/var/tmp/quarantine";
int create_quarantine_dir();
#endif //ANTIVIRUS_BSO_SETUP_H
