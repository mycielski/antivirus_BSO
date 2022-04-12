#!/bin/bash
cd ./doc || exit
./build_manpage.sh quiet
cd ..
cmake . -DCMAKE_BUILD_TYPE=Release
make || exit
mkdir ./build
mkdir ./build/release
mv ./antivirus_BSO ./build/release/avbso

echo "Creating cleanup script "
echo '''#!/bin/bash''' > ./cleanup.sh
{
  echo "rm -rf ./build"
  echo "rm -rf ./cmake-build-debug"
  echo "rm -rf ./CMakeFiles"
  echo "rm CMakeCache.txt"
  echo "rm cmake_install.cmake"
  echo "rm Makefile"
#  echo "rm doc/manpage"
  echo "rm cleanup.sh"
} >> ./cleanup.sh
chmod +x cleanup.sh
