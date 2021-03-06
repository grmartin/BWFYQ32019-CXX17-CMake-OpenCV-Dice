# 2019Q3 Benchwork: C++17 (MSVC2017, g++8, Clang (LLVM) 10), CMake, OpenCV on Mac, Windows and Linux.

## Overview

This is a first attempt at creating a simple (I hope) application with OpenCV across all major Desktop Platforms.

This project uses CMake and Hunter for package management and QT5 as a GUI.

Currently the plan is as follows (and subject to change):

1. ~~Build application + library to encode/decode expected values in to a JPEG image. : \[*COMPLETE*]~~
2. ~~Add in quick testing suite (Catch2 @ `./src/tests`): \[*COMPLETE*]~~
3. ~~Build application to read pips off dice and compare to values. : \[*COMPLETE*]~~
4. ~~Compilation Support for Linux. : \[*COMPLETE*]~~
5. Compilation Support for Windows 10. (MSVC2019 support not possible yet due to OpenCV's lack of support): \[*WIP*]
6. Update to handle live images (on simple dice) : \[*PLANNED*]
7. Improve as time goes on to detect different colors/types of pip-ed dice. : \[*PLANNED*]

Validate inter-operating system support:

1. ~~MacOS (Apple/Xcode Clang) : \[*COMPLETE*]~~
2. Linux (GCC/G++8)
3. MSVC++ 15 (2017)

## Directory Structure

- [`/src`](./src) - source code for `CVDice`
	- [`/src/tests`](./src/tests) - [Catch2](https://github.com/catchorg/Catch2) Tests
	- [`/src/annotation`](./src/annotation) - `CVDiceAnnotator` binary and Library Source Code
	- [`/src/cmake`](./src/cmake) - CMake support scripts
- [`/stock/Images`](./stock/Images) - Stock images for Testing