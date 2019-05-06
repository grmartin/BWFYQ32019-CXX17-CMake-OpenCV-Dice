# 2019Q3 Benchwork: C++17 (MSVC2019, g++8, Clang (LLVM) 10), CMake, OpenCV on Mac, Windows and Linux.

This is a first attempt at creating a simple (i hope) application with OpenCV across all major Desktop Platforms.

This project uses CMake and Hunter for package management.

Currently the plan is as follows (and subject to change):

1. ~~Build application + library to encode/decode expected values in to a JPEG image. : \[*COMPLETE*]~~
2. ~~Add in quick testing suite (Catch2 @ `./src/tests`): \[*COMPLETE*]~~
3. Build application to read pips off dice and compare to values. : \[*WIP*]
4. Update to handle live images (on simple dice) : \[*PLANNED*]
5. Improve as time goes on to detect different colors/types of pip-ed dice. : \[*PLANNED*]
