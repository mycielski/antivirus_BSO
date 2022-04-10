#!/bin/bash
cmake . -DCMAKE_BUILD_TYPE=Release
make
cd ./doc
./build_manpage.sh
cd ..
