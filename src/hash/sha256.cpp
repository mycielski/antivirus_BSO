//
// Created by tomek on 3/20/22.
//

#include <string>
#include <fstream>
#include <iostream>
#include <openssl/sha.h>
#include "sha256.h"
#include <array>

std::string& getFile(const std::string &path);

void fileSha256(const std::string &path) {
    std::string *buffer = &(getFile(path));

    std::array<unsigned char, SHA256_DIGEST_LENGTH> hash{};

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, buffer->c_str(), buffer->size());
    SHA256_Final(hash.data(), &sha256);
    delete buffer;
    std::array<char, SHA_DIGEST_LENGTH * 2 + 1> hex_output{};
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hex_output[i * 2], "%02x", hash[i]);
    }
    fprintf(stdout, "%s\n", hex_output.data());
}

std::string& getFile(const std::string &path) {
    auto *s = new std::string;

    std::fstream fp;
    fp.open(path, std::ios::in);

    if (!(fp.is_open())) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    } else {
        s ->reserve(1024);
        std::string line;
        while (fp >> line) {
            s -> append(line);
        }
    }
    fp.close();
    return *s;
}