//
// Created by tomek on 3/22/22.
//

#include "file.h"

#include "../hash/sha256.h"

File::File(const std::string &path) : path(path) {
  this->path = path;
  this->sha256 = FileSha256(path);
}

const std::string &File::GetSha256() const { return sha256; }

void File::SetMalicious(bool malicious) { File::malicious = malicious; }

bool File::IsMalicious() const { return malicious; }

const std::string &File::GetPath() const { return path; }
