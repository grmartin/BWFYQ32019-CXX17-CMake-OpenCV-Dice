// FROM https://gist.github.com/PkmX/63dd23f28ba885be53a5

// "License": Public Domain
// I, Mathias Panzenböck, place this file hereby into the public domain. Use it at your own risk for whatever you like.
// In case there are jurisdictions that don't support putting things in the public domain you can also consider it to
// be "dual licensed" under the BSD, MIT and Apache licenses, if you want to. This code is trivial anyway. Consider it
// an example on how to get the endian conversion functions on different platforms.

#ifndef PORTABLE_ENDIAN_H__
#define PORTABLE_ENDIAN_H__

#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)
#	define __WINDOWS__
#endif

#if defined(__linux__) || defined(__CYGWIN__)
#	include <endian.h>

#elif defined(__APPLE__)
#	include <libkern/OSByteOrder.h>

    constexpr auto htobe16 = [](auto x) { return OSSwapHostToBigInt16(x); };
    constexpr auto htole16 = [](auto x) { return OSSwapHostToLittleInt16(x); };
    constexpr auto be16toh = [](auto x) { return OSSwapBigToHostInt16(x); };
    constexpr auto le16toh = [](auto x) { return OSSwapLittleToHostInt16(x); };

    constexpr auto htobe32 = [](auto x) { return OSSwapHostToBigInt32(x); };
    constexpr auto htole32 = [](auto x) { return OSSwapHostToLittleInt32(x); };
    constexpr auto be32toh = [](auto x) { return OSSwapBigToHostInt32(x); };
    constexpr auto le32toh = [](auto x) { return OSSwapLittleToHostInt32(x); };

    constexpr auto htobe64 = [](auto x) { return OSSwapHostToBigInt64(x); };
    constexpr auto htole64 = [](auto x) { return OSSwapHostToLittleInt64(x); };
    constexpr auto be64toh = [](auto x) { return OSSwapBigToHostInt64(x); };
    constexpr auto le64toh = [](auto x) { return OSSwapLittleToHostInt64(x); };

#	define __BYTE_ORDER    BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN

#elif defined(__OpenBSD__)
#	include <sys/endian.h>

#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)
#	include <sys/endian.h>

    constexpr auto be16toh = [](auto x) { return betoh16(x); };
    constexpr auto le16toh = [](auto x) { return letoh16(x); };

    constexpr auto be32toh = [](auto x) { return betoh32(x); };
    constexpr auto le32toh = [](auto x) { return letoh32(x); };

    constexpr auto be64toh = [](auto x) { return betoh64(x); };
    constexpr auto le64toh = [](auto x) { return letoh64(x); };

#elif defined(__WINDOWS__)
#	include <windows.h>

#	if BYTE_ORDER == LITTLE_ENDIAN

#       if defined(_MSC_VER)
#           include <cstdlib> // stdlib.h in C
            constexpr auto htobe16 = [](auto x) { return _byteswap_ushort(x); };
            constexpr auto htole16 = [](auto x) { return (x); };
            constexpr auto be16toh = [](auto x) { return _byteswap_ushort(x); };
            constexpr auto le16toh = [](auto x) { return (x); };

            constexpr auto htobe32 = [](auto x) { return _byteswap_ulong(x); };
            constexpr auto htole32 = [](auto x) { return (x); };
            constexpr auto be32toh = [](auto x) { return _byteswap_ulong(x); };
            constexpr auto le32toh = [](auto x) { return (x); };

            constexpr auto htobe64 = [](auto x) { return _byteswap_uint64(x); };
            constexpr auto htole64 = [](auto x) { return (x); };
            constexpr auto be64toh = [](auto x) { return _byteswap_uint64(x); };
            constexpr auto le64toh = [](auto x) { return (x); };

#       elif defined(__GNUC__) || defined(__clang__)
            constexpr auto htobe16 = [](auto x) { return __builtin_bswap16(x); };
            constexpr auto htole16 = [](auto x) { return (x); };
            constexpr auto be16toh = [](auto x) { return __builtin_bswap16(x); };
            constexpr auto le16toh = [](auto x) { return (x); };

            constexpr auto htobe32 = [](auto x) { return __builtin_bswap32(x); };
            constexpr auto htole32 = [](auto x) { return (x); };
            constexpr auto be32toh = [](auto x) { return __builtin_bswap32(x); };
            constexpr auto le32toh = [](auto x) { return (x); };

            constexpr auto htobe64 = [](auto x) { return __builtin_bswap64(x); };
            constexpr auto htole64 = [](auto x) { return (x); };
            constexpr auto be64toh = [](auto x) { return __builtin_bswap64(x); };
            constexpr auto le64toh = [](auto x) { return (x); };
#       else
#           error platform not supported
#       endif
#	else
#		error byte order not supported
#	endif

#	define __BYTE_ORDER    BYTE_ORDER
#	define __BIG_ENDIAN    BIG_ENDIAN
#	define __LITTLE_ENDIAN LITTLE_ENDIAN
#	define __PDP_ENDIAN    PDP_ENDIAN

#else
#	error platform not supported

#endif
#endif