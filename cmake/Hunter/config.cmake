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
