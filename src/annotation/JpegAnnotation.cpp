//
// Created by Glenn R. Martin on 4/29/2019.
//

#include <functional>
#include <iostream>
#include <fstream>
#include <map>

#include "JpegAnnotation.h"
#include "Endian.h"
#include "Defer.h"
#include "VecByte.h"
#include "Chunk.h"

using namespace jpeganno;

constexpr bool ENABLE_DEBUGGING = false;
#define CDL_STREAM(c, s) if (c) s
#define DBG_STREAM(s) CDL_STREAM(ENABLE_DEBUGGING, s)

typedef  uint64_t stm_off_t;

// `sizeof` returns number of chars something makes up... thus in R = sizeof(T), R is (R*CHAR_BIT) bits large. If CHAR_BIT isnt 8... were packed wrong.
static_assert(CHAR_BIT == 8, "This platform is strange... a Char should be 8 bits... Type assumptions will be wrong...");

static_assert(
        sizeof(stm_off_t) >= (sizeof(std::streamoff) == sizeof(std::streamsize)),
        "Stream positioning will blow up. Abend.");

// Anywhere in the file 0xFF would be found as a NON-Atomic Unit Header it is escaped as 0xFF00.
// See ISO/IEC 10918-1:1993(E) Pg32 / (CCITT Rec. T.81 (1992 E))
constexpr uint8_t JPEG_PRECURSOR = 0xFF; /* All JPEG blocks are 2 bytes for a precursor, this + the marker */
constexpr uint8_t SOI = 0xD8;            /* Start of Image */
constexpr uint8_t EOI = 0xD9;            /* End of Image */
constexpr uint8_t APP(unsigned char n) { return ((unsigned char)0xE0 | n); } /* Application Specific Section N (valid range 0x0-0xF) */

constexpr uint8_t CVDICE_MARKER = APP(0xD); /* D for Dice */ // NOLINT(cert-err58-cpp)

#define TO_FILE_ORDER_16 htobe16
#define TO_FILE_ORDER_32 htobe32
#define TO_FILE_ORDER_64 htobe64
#define FR_FILE_ORDER_16 be16toh
#define FR_FILE_ORDER_32 be32toh

extern uint64_t typeMarker();

#pragma pack(push, 1)
struct sPackedSet {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
    unsigned int value1: 3;
    unsigned int value2: 3;
    unsigned int value3: 3;
    unsigned int value4: 3;
    unsigned int value5: 3;
    unsigned int value6: 3;
    unsigned int value7: 3;
    unsigned int value8: 3;
    unsigned int value9: 3;
    unsigned int value10: 3;
#pragma clang diagnostic pop
};

union PackedSet {
    struct sPackedSet st;
    uint32_t bytes;
};

constexpr auto VALUES_PER_PACKEDSET = 10u;
static_assert(sizeof(struct sPackedSet) == 4, "Each set should be 32 bits (4 bytes)");
static_assert(sizeof(union PackedSet) == 4, "Each set's union should be 32 bits (4 bytes)");
#pragma pack(pop)

uint64_t typeMarker() {
    constexpr auto CVDMARKER1 = "GRM:";
    constexpr auto CVDMARKER2 = "CVD:";
    constexpr auto cc = [](char const p[5]) -> uint32_t {
        return (p[0] << 24u) | (p[1] << 16u) | (p[2] << 8u) | p[3]; // NOLINT(hicpp-signed-bitwise)
    };
    const static uint64_t TYPE_MARKER = TO_FILE_ORDER_64(
            (static_cast<uint64_t>(cc(CVDMARKER1)) << 32u) | cc(CVDMARKER2));
    return TYPE_MARKER;
}

inline void testIsFile(const fs::path &jpegFilePath) {
    if (!is_regular_file(jpegFilePath)) throw std::runtime_error("Path provided is not a file.");
}

inline void testIsOpen(const std::function<bool()> &is_open) {
    if (!is_open()) throw std::runtime_error("Unable to open path.");
}

template<typename T>
inline std::byte eat1(T &stream) {
    unsigned char byte = 0;
    stream >> byte;
    return std::byte{byte};
}

template<typename K, typename M>
inline bool map_has_key(M &map, K key) {
    return map.find(key) != map.end();
}

template <typename T> T limit_between(T low, T high, T val) {
    return val < low ? low : val > high ? high : val;
}

std::vector<uint8_t> JpegAnnotation::parseExpectedValues(const fs::path &jpegFilePath) {
    testIsFile(jpegFilePath);

    std::ifstream stream(jpegFilePath.generic_string(), std::ios::binary | std::ios::in);

    testIsOpen([&stream]() { return stream.is_open(); });

    auto finallyCloseStream = defer([&stream]() { if (stream.is_open()) { stream.close(); }});

    std::vector<uint8_t> returnValue;
    returnValue.reserve(VALUES_PER_PACKEDSET);

    std::byte last{0x00};
    std::byte curr{0x00};

    while (stream.good()) {
        last = curr;
        curr = eat1(stream);

        if (last == std::byte{JPEG_PRECURSOR} && curr == std::byte{CVDICE_MARKER}) {
            DBG_STREAM(std::cout) << "Found CVDice Marker (FFED) @" << stream.tellg() << std::endl;
            uint16_t length;
            stream.read(reinterpret_cast<char*>(&length), sizeof(uint16_t));
            length = FR_FILE_ORDER_16(length);

            if (length >= sizeof(typeMarker())) {
                uint64_t contentMarker;
                stream.read(reinterpret_cast<char*>(&contentMarker), sizeof(uint64_t));
                if (contentMarker == typeMarker()) {
                    auto left = length - sizeof(uint16_t) - sizeof(uint64_t);
                    auto numberSets = left / sizeof(union PackedSet);

#define checkSetN(s, n) \
    if (s.st.value ## n == 0 ) continue; \
    returnValue.push_back(s.st.value ## n)

                    for (auto i = 0; numberSets > i; i++) {
                        uint32_t set;
                        stream.read(reinterpret_cast<char*>(&set), sizeof(uint32_t));

                        auto aSet = PackedSet{};
                        aSet.bytes = FR_FILE_ORDER_32(set);

                        checkSetN(aSet, 1);
                        checkSetN(aSet, 2);
                        checkSetN(aSet, 3);
                        checkSetN(aSet, 4);
                        checkSetN(aSet, 5);
                        checkSetN(aSet, 6);
                        checkSetN(aSet, 7);
                        checkSetN(aSet, 8);
                        checkSetN(aSet, 9);
                        checkSetN(aSet, 10);
                    }
#undef checkSetN
                }
            }
        }
    }

    return returnValue;
}

template <typename T> T getHsz() { return 2; };

void JpegAnnotation::writeExpectedValues(const fs::path &jpegFilePath, const std::vector<uint8_t> &expectations) {
    testIsFile(jpegFilePath);

    auto streamFlags = std::ios::binary | std::ios::out | std::ios::in;

    std::fstream stream(jpegFilePath.generic_string(), streamFlags);
    stream.unsetf(std::ios::skipws);

    testIsOpen([&stream]() { return stream.is_open(); });

    auto finallyCloseStream = defer([&stream]() { if (stream.is_open()) { stream.close(); }});

    std::byte last{0x00};
    std::byte curr{0x00};

    struct jpgBlockLocation {
        uint16_t hSz;
        stm_off_t st;
        uint16_t lead;
        uint16_t pSz;
    };

    constexpr auto setLocation = [](auto location, auto size) {
        struct jpgBlockLocation loc = jpgBlockLocation{getHsz<uint16_t>(), static_cast<uint64_t>(location), 4, size};
        return static_cast<struct jpgBlockLocation>(loc);
    };
    constexpr auto setImgLocation = [](auto location) {
        return static_cast<struct jpgBlockLocation>(jpgBlockLocation{getHsz<uint16_t>(), static_cast<uint64_t>(location), 2, 0});
    }; // SOI and EOI markers have no size, they just are.

    std::map<std::byte, struct jpgBlockLocation> locations;
    VecByte fileArray;

    fileArray.reserve(fs::file_size(jpegFilePath));

    int skip = 0;

    while (!stream.fail()) {
        if (--skip > 0) continue;
        last = curr;
        curr = eat1(stream);

        fileArray.push_back(curr);

        if (last != std::byte{JPEG_PRECURSOR}) continue;

        if (curr == std::byte{CVDICE_MARKER}) {
            stm_off_t markerLocation = (stm_off_t)stream.tellg() - getHsz<stm_off_t>();

            DBG_STREAM(std::cout) << "Found CVDice Marker (FFED) @" << std::dec << markerLocation << std::endl;

            uint16_t length;
            stream.read(reinterpret_cast<char*>(&length), sizeof(uint16_t));
            length = FR_FILE_ORDER_16(length);

            if (length >= sizeof(typeMarker())) {
                uint64_t contentMarker;
                stream.read(reinterpret_cast<char*>(&contentMarker), sizeof(uint64_t));
                if (contentMarker == typeMarker()) {
                    skip = length;
                    // we need to reject what weve already consumed... (the header)
                    for (int reject = 0; getHsz<int>() > reject; reject++) {
                        fileArray.pop_back();
                    }
                }
            }
        } else if (curr == std::byte{SOI}) {
            stm_off_t markerLocation = (stm_off_t)stream.tellg() - getHsz<stm_off_t>();
            locations[std::byte{SOI}] = setImgLocation(markerLocation);
            DBG_STREAM(std::cout) << "Found Start of Image Marker (FFD8) @" << std::dec << markerLocation << std::endl;
        } else if (curr == std::byte{EOI}) {
            stm_off_t markerLocation = (stm_off_t)stream.tellg() - getHsz<stm_off_t>();
            locations[std::byte{EOI}] = setImgLocation(fileArray.size());
            DBG_STREAM(std::cout) << "Found End of Image Marker (FFD9) @" << std::dec << markerLocation << std::endl;
            break;
        }
    }

    stream.close();

    if (!map_has_key(locations, std::byte{SOI}) || !map_has_key(locations, std::byte{EOI})) {
        std::cerr << "Invalid image file provided." << std::endl;
        return;
    }

    auto eoiLocation = locations[std::byte{EOI}];

    VecByte newBytes;
    auto expectationSets = chunk(expectations, 10);

    std::for_each(expectationSets.begin(), expectationSets.end(), [&newBytes](std::vector<uint8_t> items) {
        union PackedSet set = {0};
        const auto sz = items.size();

#define ifSetN(s, sz, n) if (sz >= n) set.st.value ## n = limit_between<uint8_t>(1, 6, items.at(n-1))

        ifSetN(set, sz, 1);
        ifSetN(set, sz, 2);
        ifSetN(set, sz, 3);
        ifSetN(set, sz, 4);
        ifSetN(set, sz, 5);
        ifSetN(set, sz, 6);
        ifSetN(set, sz, 7);
        ifSetN(set, sz, 8);
        ifSetN(set, sz, 9);
        ifSetN(set, sz, 10);

#undef ifSetN

        auto structVec = toVecByte(TO_FILE_ORDER_32(set.bytes));
        newBytes.insert(newBytes.end(), structVec.begin(), structVec.end());
    });

    uint16_t len = sizeof(uint16_t) + sizeof(typeMarker()) + newBytes.size();
    VecByte blockBytes;
    blockBytes.reserve(getHsz<VecByte::size_type>() + len);
    blockBytes.push_back(std::byte{JPEG_PRECURSOR});
    blockBytes.push_back(std::byte{CVDICE_MARKER});
    append(blockBytes, toVecByte(TO_FILE_ORDER_16(len)));
    append(blockBytes, toVecByte(typeMarker()));
    append(blockBytes, newBytes);

    fileArray.insert(fileArray.begin() + (eoiLocation.st - eoiLocation.hSz), blockBytes.begin(), blockBytes.end());

    stream.open(jpegFilePath.generic_string(), streamFlags | std::ios::trunc);
    stream.unsetf(std::ios::skipws);

    testIsOpen([&stream]() { return stream.is_open(); });

    DBG_STREAM(std::cout) << "Writing, Last 25:" << std::endl;
    int i = 0;
    std::for_each(fileArray.begin(), fileArray.end(), [&stream, &i, &fileArray](std::byte byte) {
        stream << static_cast<char>(byte);
        i++;

        if (i > (fileArray.size() - 25)) {
            DBG_STREAM(std::cout) << std::hex << static_cast<int>(byte) << ":";
        }
    });
    DBG_STREAM(std::cout) << "." << std::endl;

    stream.flush();

    DBG_STREAM(std::cout) << "Proc done." << std::endl;
}
