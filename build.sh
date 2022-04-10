#!/bin/bash
cd ./doc || exit
./build_manpage.sh
cd ..
cmake . -DCMAKE_BUILD_TYPE=Release
make || exit
mkdir ./build
mkdir ./build/release
mv ./antivirus_BSO ./build/release/avbso

echo "Creating cleanup script "
echo '''#!/bin/bash''' > ./cleanup.sh
echo '''rm -rf ./build''' >> ./cleanup.sh
echo '''rm -rf ./cmake-build-debug''' >> ./cleanup.sh
echo '''rm -rf ./CMakeFiles''' >> ./cleanup.sh
echo '''rm CMakeCache.txt''' >> ./cleanup.sh
echo '''rm cmake_install.cmake''' >> ./cleanup.sh
echo '''rm Makefile''' >> ./cleanup.sh
echo '''rm cleanup.sh''' >> ./cleanup.sh
chmod +x cleanup.sh
