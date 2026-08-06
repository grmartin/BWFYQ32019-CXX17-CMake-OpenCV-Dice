# Hunter's pinned PNG package (1.6.36-p4) still contains libpng's legacy
# classic-Mac fp.h include path, guarded by `TARGET_OS_MAC` (always defined
# on any Apple build) and an inner `!defined(__MATH_H__)` guard meant to
# detect whether <math.h> was already included. Newer Xcode/Clang trips the
# outer guard before <math.h> has been pulled in, so it tries `#include
# <fp.h>` -- a header that hasn't existed since classic (pre-OSX) Mac OS --
# and fails with "fatal error: 'fp.h' file not found".
#
# Force-including the real <math.h> first makes it set its own internal
# include guard genuinely (Apple's libc math.h happens to define exactly
# `__MATH_H__`), so by the time pngpriv.h's own `#if !defined(__MATH_H__)`
# check runs, it correctly sees math.h was already loaded and skips the
# dead fp.h branch -- while still getting real declarations for floor(),
# frexp(), etc. (Pre-defining __MATH_H__ via -D instead, without actually
# including math.h, was tried first and backfired: it poisons math.h's own
# guard so its *real* declarations never load when something later does
# `#include <math.h>` normally.)
#
# We stay on Hunter's own libpng fork (rather than a newer upstream
# release) deliberately: it's the one Hunter's bundled
# cmake/find/FindPNG.cmake is written for (it hardcodes the `PNG::png`
# lowercase imported target name), whereas upstream pnggroup/libpng's own
# CMake config only exports `PNG::PNG`, which breaks OpenCV's
# target_link_libraries(... PNG::png ...) instead.
#
# TARGET_OS_MAC is never defined on Windows/Linux, so this flag is a no-op
# there -- this fix is macOS-only in effect.
#
# Separately, this same 2018-era fork's ARM NEON runtime-detection source
# list (PNG_ARM_NEON_FILE) was never updated for Apple Silicon (arm64
# macOS), so with the default "check" mode it fails to build on M-series
# Macs ("PNG_ARM_NEON_FILE undefined"). Disable NEON detection outright
# rather than chase down the missing per-platform detection source; this
# only costs PNG decode SIMD speed, which doesn't matter for this project.
hunter_config(
    PNG
    VERSION 1.6.36-p4
    CMAKE_ARGS
        PNG_TESTS=OFF
        PNG_ARM_NEON=off
        "CMAKE_C_FLAGS=-include math.h"
)

# Hunter's OpenCV recipe tops out at 4.12.0-p1 (no 5.x), so OpenCV 5 is
# pinned here as a custom version pointing straight at the upstream release
# tarball. Unlike Hunter's own "-pN" OpenCV forks, the upstream source is
# not "hunterized" -- it won't call back into Hunter for zlib/libpng/libjpeg
# -- so OPENCV_FORCE_3RDPARTY_BUILD makes it compile its own bundled copies
# of every enabled 3rdparty codec instead of picking up whatever happens to
# be installed system-wide. A side effect worth knowing: nothing in this
# build pulls Hunter's PNG package anymore, so the PNG workaround block
# above is expected to be inert (it's kept in case anything ever routes
# through Hunter's PNG again, and as documentation of the trap).
#
# BUILD_LIST keeps the build to the four modules this project actually
# uses (OpenCV's build resolves their inter-module dependencies itself).
# OpenCV 5 requires C++17 -- the same standard this project already builds
# with -- and its compiler floor (MSVC 2017 19.14 / GCC 8 / Clang 9)
# matches this project's documented minimums.
hunter_config(
    OpenCV
    VERSION 5.0.0
    URL "https://github.com/opencv/opencv/archive/refs/tags/5.0.0.tar.gz"
    SHA1 "67e27a1ed9e9998bba211691dac766a8740fc476"
    CMAKE_ARGS
        BUILD_LIST=core,imgproc,imgcodecs,highgui,geometry
        OPENCV_FORCE_3RDPARTY_BUILD=ON
        BUILD_TESTS=OFF
        BUILD_PERF_TESTS=OFF
        BUILD_EXAMPLES=OFF
        BUILD_opencv_apps=OFF
        WITH_FFMPEG=OFF
        WITH_PROTOBUF=OFF
)
