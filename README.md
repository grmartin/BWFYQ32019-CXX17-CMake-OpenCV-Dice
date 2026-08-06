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
sudo apt install qt6-base-dev qt6-base-dev-tools libqt6opengl6-dev
```

`qt6-base-dev` covers Core, Gui, Widgets, Concurrent, and Test, but Debian splits the `OpenGL` component's CMake config out into `libqt6opengl6-dev` separately — without it, `find_package(Qt6 ... COMPONENTS OpenGL)` fails with `Could NOT find Qt6OpenGL (missing: Qt6OpenGL_DIR)` even though `qt6-base-dev` is installed. Debian stable tends to trail the latest upstream Qt 6 release (e.g. Debian 13 "trixie" currently ships 6.8.x against an upstream 6.11.x) — that's expected and fine for this project.

## The Qt GUI: controls reference

Running `CVDice <image.jpg>` (without `--noQT`) opens the interactive tuning UI. The image runs through the transformer pipeline

> `ImageOrigin → Colorer → AdaptiveThresholder → Edger → Contouring → Terminus`

and the render area at the bottom shows the output of the *last enabled* stage. The list above it holds one row per tunable parameter: a checkbox, the parameter name, a slider, and the current raw slider value.

**Checkboxes** enable/disable an entire pipeline *stage*; a disabled stage passes its input through untouched. Rows without a visible checkbox are extra parameters of the same stage as the nearest checkboxed row above them. Sliders always show their raw integer value; the table below gives what each integer actually means. If a combination makes OpenCV reject a frame mid-chain (e.g. disabling **Color Value** so unconverted BGR reaches the thresholder), the exception is swallowed and the preview simply stops updating until the chain is valid again — that's by design, not a hang.

| Row | Stage (default) | Range | What the value means |
|---|---|---|---|
| **Color Value** | Colorer (enabled, `1`) | 0–1 | Index into the Colorer's conversion list: `0` = `COLOR_BGR2GRAY`, `1` = `COLOR_RGB2GRAY`. Both grayscale the frame; they differ only in assumed channel order (swaps the red/blue luminance weights). A large set of further conversions (HSV, Lab, YUV, …) exists commented-out in `Colorer.cpp` — uncommenting extends this slider's range. |
| *(no row)* | AdaptiveThresholder (always on) | — | Currently has **no UI rows** (its two toolbars are commented out in `QT6Main.cpp`); it runs fixed: `THRESH_BINARY`, `ADAPTIVE_THRESH_MEAN_C`, block size 5, C 11. |
| **Canny Kern** | Edger (**disabled** by default, `0`) | 0–2 | Sobel aperture for Canny, mapped `3 + (v*2)` → `0`=3, `1`=5, `2`=7. This row's checkbox is the Edger's on/off switch. |
| **Canny Thresh Value** | Edger | 0–100 | Canny's *lower* hysteresis threshold, in 8-bit intensity units. |
| **Canny Ratio** | Edger | 0–7 | Multiplier giving the *upper* hysteresis threshold (`upper = lower × ratio`). Canny's author recommends 2–3; `0` collapses both thresholds together. |
| **Retrieval Mode** | Contouring (**disabled** by default, `2`) | 0–4 | `cv::RetrievalModes` verbatim: `0` `RETR_EXTERNAL` (outermost only), `1` `RETR_LIST` (flat), `2` `RETR_CCOMP` (two-level: outlines + holes — what pip counting expects), `3` `RETR_TREE` (full nesting), `4` `RETR_FLOODFILL`. This row's checkbox is the Contouring stage's on/off switch. |
| **Approx Type** | Contouring | 0–3 | `cv::ContourApproximationModes`, stored off-by-one (`mode = v + 1`): `0` `CHAIN_APPROX_NONE`, `1` `CHAIN_APPROX_SIMPLE`, `2` `CHAIN_APPROX_TC89_L1`, `3` `CHAIN_APPROX_TC89_KCOS`. |

With Contouring enabled, detected contours are drawn colored by nesting depth, rough shapes are tagged in-image (`S` = square/die face, `C` = circle/pip), and each run prints `EQUAL PIPS? TRUE|FALSE` to stdout comparing the counted pips against the values embedded in the JPEG by `CVDiceAnnotator`.

## Directory Structure

- [`/src`](./src) - source code for `CVDice`
	- [`/src/tests`](./src/tests) - [Catch2](https://github.com/catchorg/Catch2) Tests
	- [`/src/annotation`](./src/annotation) - `CVDiceAnnotator` binary and Library Source Code
	- [`/src/cmake`](./src/cmake) - CMake support scripts
- [`/stock/Images`](./stock/Images) - Stock images for Testing