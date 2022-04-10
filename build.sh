#!/bin/bash
cmake . -DCMAKE_BUILD_TYPE=Release
make
cd ./doc || exit
./build_manpage.sh
cd ..
mv ./antivirus_BSO ./avbso
