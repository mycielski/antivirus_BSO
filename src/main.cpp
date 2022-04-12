#include <iostream>
#include "Scanner.h"
#include "setup.h"
#include <chrono>
#include <thread>
#include <csignal>
#include <cstring>

void signal_callback_handler(int signum) {
    perror("\nCaught interrupt signal. Exiting... ");
    fcloseall();
    exit(signum);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: avbso <hashes_list> <path_to_scan>" << std::endl;
        return 1;
    }
    auto start = std::chrono::steady_clock::now();

    struct sigaction sigIntHandler{};
    sigIntHandler.sa_handler = signal_callback_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, nullptr);

    auto scanPath = argv[2];
    auto dbPath = argv[1];
    auto hashType = HashType::SHA256;
    create_quarantine_dir();
    std::cout << "Reading hashes from " << dbPath << "... ";
    Scanner scanner(scanPath, dbPath, hashType);
    std::cout << "Done." << std::endl;
    // if path to scan is "/" display warning and sleep for 5 seconds
    if (strcmp(scanPath, "/") == 0) {
        std::cout << "WARNING: Scanning root directory. This may take a VERY long time." << std::endl;
        std::cout << "Press Ctrl+C to exit. The scan will start in 5 seconds otherwise." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    std::cout << "Commencing scan of " << scanPath << std::endl;
    scanner.scan();
    fcloseall();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Scan completed in " << elapsed_time.count() << "ms" << std::endl;
    // if the scan took less than a second, sleep to prevent quarantine folders from being overwritten
    if (elapsed_time.count() < 1000) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1001 - elapsed_time.count()));
    }
    return 0;
}


