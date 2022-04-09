
#include "Scanner.h"
#include "setup.h"

int main(int argc, char *argv[]) {
    auto path = "../";
    auto hashType = HashType::SHA256;
    auto dbPath = "../examples/hashes";
    create_quarantine_dir();
    Scanner scanner(path, dbPath, hashType);
    scanner.scan();
    return 0;
}
