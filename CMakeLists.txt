cmake_minimum_required(VERSION 3.21)
project(antivirus_BSO VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

add_executable(antivirus_BSO src/main.cpp src/hash/sha256.cpp src/hash/sha256.h)

target_link_libraries(${PROJECT_NAME} PUBLIC ssl crypto)