
#include <iostream>
#include "Scanner.h"
#include "setup.h"

int main(int argc, char *argv[]) {
    auto path = "/";//argv[0];
    auto dbPath = argv[1];
    auto hashType = HashType::SHA256;
    create_quarantine_dir();
    std::cout << "Reading hashes from " << dbPath << "... ";
    Scanner scanner(path, dbPath, hashType);
    std::cout << "Done." << std::endl;
    std::cout << "Commencing scan of " << path << std::endl;
    scanner.scan();
    return 0;
}
