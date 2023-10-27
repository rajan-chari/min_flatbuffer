Build & instructions
==================
- git submodule update --init --recursive
- mkdir build
- cmake -B build --preset basic
- cmake --build build
- build\Debug\MyExecutable.exe