# 2019Q3 Benchwork: C++17 (MSVC2017, g++8, Clang (LLVM) 10), CMake, OpenCV on Mac, Windows and Linux.

## Overview

This is a first attempt at creating a simple (I hope) application with OpenCV across all major Desktop Platforms.

This project uses CMake and Hunter for package management (OpenCV is 5.0.0, pinned as an upstream tarball through a Hunter custom version — see `cmake/Hunter/config.cmake`) and Qt 6 as a GUI.

Currently the plan is as follows (and subject to change):

1. ~~Build application + library to encode/decode expected values in to a JPEG image. : \[*COMPLETE*]~~
2. ~~Add in quick testing suite (Catch2 @ `./src/tests`): \[*COMPLETE*]~~
3. ~~Build application to read pips off dice and compare to values. : \[*COMPLETE*]~~
4. ~~Compilation Support for Linux. : \[*COMPLETE*]~~
5. Compilation Support for Windows 10/11. (Originally blocked on OpenCV's lack of MSVC 2019 support — no longer an issue as of OpenCV 5, which supports MSVC 2017 19.14+/2019/2022. The GUI additionally needs MSVC 2022, a Qt 6 requirement — see Prerequisites.): \[*WIP*]
6. Update to handle live images (on simple dice) : \[*PLANNED*]
7. Improve as time goes on to detect different colors/types of pip-ed dice. : \[*PLANNED*]

Validate inter-operating system support:

1. ~~MacOS (Apple/Xcode Clang) : \[*COMPLETE*]~~
2. Linux (GCC/G++8)
3. MSVC++ 15 (2017)

## Prerequisites

The GUI (`CVDiceQT`) needs **Qt 6** available as a system/package-manager install. Hunter (used for the other dependencies, see [`CLAUDE.md`](./CLAUDE.md)) can't provide it as a fallback here — its bundled Qt recipe only goes up to Qt 5.12.3 and Qt 6 changed build systems entirely, so that recipe doesn't carry forward. As of Qt 6.11 (the current release), install one of the following before configuring:

### Windows 11

Qt 6.11 requires **MSVC 2022** (Qt 6 dropped support for the MSVC 2017 toolset this project otherwise targets, so building the GUI means building with 2022 instead).

Using [vcpkg](https://vcpkg.io/):

```powershell
vcpkg install qtbase[gui,widgets,opengl,concurrent,testlib]:x64-windows
```

Hunter already owns `CMAKE_TOOLCHAIN_FILE` for this project, so point CMake at the vcpkg install via `CMAKE_PREFIX_PATH` rather than vcpkg's own toolchain file:

```powershell
cmake -S src -B cmake-build-debug -DCMAKE_PREFIX_PATH="<vcpkg-root>\installed\x64-windows"
```

Alternatively, use the official [Qt Online Installer](https://www.qt.io/download-qt-installer-oss) (free Qt Account required) and select the MSVC 2022 64-bit kit.

### macOS (Homebrew)

```bash
brew install qt
```

Homebrew's `qt` formula is Qt 6 (`qt@5` is the separate, deprecated Qt 5 formula). It installs into Homebrew's standard prefix, so `find_package(Qt6 ...)` should find it with no extra CMake flags.

### Linux (Debian-based)

```bash
sudo apt install qt6-base-dev qt6-base-dev-tools
```

That one package covers Core, Gui, Widgets, OpenGL, Concurrent, and Test — everything this project links against. Debian stable tends to trail the latest upstream Qt 6 release (e.g. Debian 13 "trixie" currently ships 6.8.x against an upstream 6.11.x) — that's expected and fine for this project.

## Directory Structure

- [`/src`](./src) - source code for `CVDice`
	- [`/src/tests`](./src/tests) - [Catch2](https://github.com/catchorg/Catch2) Tests
	- [`/src/annotation`](./src/annotation) - `CVDiceAnnotator` binary and Library Source Code
	- [`/src/cmake`](./src/cmake) - CMake support scripts
- [`/stock/Images`](./stock/Images) - Stock images for Testing