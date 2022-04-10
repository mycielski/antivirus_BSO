#!/bin/bash
cd ./doc || exit
./build_manpage.sh
cd ..
cmake . -DCMAKE_BUILD_TYPE=Release
make
mv ./antivirus_BSO ./avbso
