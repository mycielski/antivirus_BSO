//
// Created by tomek on 4/9/22.
//

#ifndef ANTIVIRUS_BSO_SETUP_H
#define ANTIVIRUS_BSO_SETUP_H

#include <string>

const std::string kQuarantineDirectory = "/var/tmp/quarantine";
int CreateQuarantineDir();
#endif  // ANTIVIRUS_BSO_SETUP_H
