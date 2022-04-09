//
// Created by tomek on 3/20/22.
//

#include <string>
#include <fstream>
#include <iostream>
#include <openssl/sha.h>
#include "sha256.h"
#include <array>
#include <iomanip>
#include <cstring>

std::string &getFile(const std::string &path);

std::string fileSha256(const std::string &path) {
    std::ifstream fp(path, std::ios::in | std::ios::binary);

    if (not fp.good()) {
        std::ostringstream os;
        os << "Cannot open \"" << path << "\": " << std::strerror(errno) << ".";
        throw std::runtime_error(os.str());
    }

    constexpr const std::size_t buffer_size{1 << 12};
    char buffer[buffer_size];

    unsigned char hash[SHA256_DIGEST_LENGTH] = {0};

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    while (fp.good()) {
        fp.read(buffer, buffer_size);
        SHA256_Update(&ctx, buffer, fp.gcount());
    }

    SHA256_Final(hash, &ctx);
    fp.close();

    std::ostringstream os;
    os << std::hex << std::setfill('0');

    for (unsigned char i : hash) {
        os << std::setw(2) << static_cast<unsigned int>(i);
    }

    return os.str();

}

std::string &getFile(const std::string &path) {
    auto *s = new std::string;

    std::fstream fp;
    fp.open(path, std::ios::in);

    if (!(fp.is_open())) {
        perror("Error opening File");
        exit(EXIT_FAILURE);
    } else {
        s->reserve(1024);
        std::string line;
        while (fp >> line) {
            s->append(line);
        }
    }
    fp.close();
    return *s;
}