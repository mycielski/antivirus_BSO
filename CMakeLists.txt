cmake_minimum_required(VERSION 3.21)
project(antivirus_BSO VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

add_executable(antivirus_BSO src/main.cpp src/hash/sha256.cpp src/hash/sha256.h src/file/file.cpp src/file/file.h src/Scanner.cpp src/Scanner.h src/database/Db.cpp src/database/Db.h src/setup.cpp src/setup.h)

target_link_libraries(${PROJECT_NAME} PUBLIC ssl crypto)