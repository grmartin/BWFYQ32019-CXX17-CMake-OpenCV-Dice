//
// Created by Glenn R. Martin on 2019-05-04.
//

#include <boost/filesystem.hpp>

#include "../Testing.hpp"

#include "../../annotation/VecByte.h"
#include "../../annotation/JpegAnnotation.h"
#include "../../annotation/Strings.h"

#ifndef CVDICE_JPEGANNOTATION_TEST_H
#define CVDICE_JPEGANNOTATION_TEST_H

TEST_CASE("JPEG Annotation", "[library]") {
    const std::string extension = ".jpg";
    uint64_t jpegDataSz;
    fs::path onepxstock_file_abspath;
    fs::path tmpPath;
    std::function<fs::path(std::string)> safeFileName;
    std::function<void(fs::path)> copyBlankJpeg;

    SETUP {
        auto jpegData = get1PxJpeg({});
        jpegDataSz = jpegData.size();

        REQUIRE(!jpegData.empty());

        tmpPath = fs::temp_directory_path() / fs::unique_path();
        fs::create_directories(tmpPath);

        REQUIRE(fs::exists(tmpPath));

        onepxstock_file_abspath = tmpPath / ("01DA2CRHGR9P7J0FXJKPYREY84" + extension);

        FREE_SCOPE {
            std::ofstream outfile(onepxstock_file_abspath.generic_string(), std::ios::out | std::ios::binary);
            outfile.write(reinterpret_cast<const char *>(&jpegData[0]), jpegData.size());
            outfile.close();
        }

        REQUIRE(fs::exists(onepxstock_file_abspath));
        REQUIRE(fs::file_size(onepxstock_file_abspath) == jpegDataSz);

        const std::regex unsafeFSMatcher = std::regex(R"([.,<>?/"':;{}|+)(*&^%$#@!~`=[\]\\\s\cG\b\x1B\f\v])");

        const auto newFileBase = "01DA31PMXKSSKHVPKTCTKHJ6RJ_";

        auto regex_replace = [](std::string const &in, std::regex const &match, std::string const &replace) {
            return std::regex_replace(in, match, replace);
        };

        safeFileName = [unsafeFSMatcher, regex_replace, tmpPath, extension, newFileBase](std::string testValues) {
            return tmpPath / (newFileBase + regex_replace(testValues, unsafeFSMatcher, "_") + extension);
        };

        REQUIRE(safeFileName("4#2*3,1") == (tmpPath / (std::string(newFileBase) + "4_2_3_1" + extension)));

        copyBlankJpeg = [&onepxstock_file_abspath, &jpegDataSz](fs::path newPath) {
            fs::copy_file(onepxstock_file_abspath, newPath);
        };
    }

    auto toEightBitVec = [](std::string str) {
        const std::regex regex("[,;]");
        auto const values = split(trim(str), regex);

        std::vector<uint8_t> valueInts;
        valueInts.reserve(values.size());

        for (auto &value: values) {
            valueInts.push_back(std::stoi(value));
        }

        return valueInts;
    };

#define MARKER(sz1, sz2, values...) { 0xFF, 0xED, sz1, sz2,                              \
                                      0x47, 0x52, 0x4D, 0x3A, 0x43, 0x56, 0x44, 0x3A,    \
                                      values                                             \
                                    }

    std::function<bool(jpeganno::VecByte, std::vector<unsigned char>)> subsection_equality =
            [](jpeganno::VecByte contents, std::vector<unsigned char> subsection_expectation) {
                return std::equal(contents.begin(), contents.end(),
                                  subsection_expectation.begin(),
                                  [](std::byte a, const char b) { return a == std::byte(b); });
            };

    SECTION("Writing to empty image") {
        std::string subsection_value;
        std::vector<unsigned char> subsection_bytes;

        subsection_value = "1,2,3,4,5,6";
        subsection_bytes = get1PxJpeg(MARKER(0x00, 0x0E, /*v*/ 0x00, 0x03, 0x58, 0xD1));
        SECTION("Should write 1,2,3,4,5,6 to data") {
            auto path = safeFileName(subsection_value);
            CAPTURE(path);
            copyBlankJpeg(path);

            REQUIRE(fs::exists(path));
            REQUIRE(fs::file_size(path) == jpegDataSz);

            jpeganno::JpegAnnotation::writeExpectedValues(path.generic_string(), toEightBitVec(subsection_value));

            const auto file_data_bytes_ = jpeganno::read(path.generic_string());
            CAPTURE(file_data_bytes_, subsection_bytes);
            REQUIRE(subsection_equality(file_data_bytes_, subsection_bytes));
        }

        subsection_value = "6";
        subsection_bytes = get1PxJpeg(MARKER(0x00, 0x0E, /*v*/ 0x00, 0x00, 0x00, 0x06));
        SECTION("Should write 6 to data") {
            auto path = safeFileName(subsection_value);
            CAPTURE(path);
            copyBlankJpeg(path);

            REQUIRE(fs::exists(path));
            REQUIRE(fs::file_size(path) == jpegDataSz);

            jpeganno::JpegAnnotation::writeExpectedValues(path.generic_string(), toEightBitVec(subsection_value));

            const auto file_data_bytes_ = jpeganno::read(path.generic_string());
            CAPTURE(file_data_bytes_, subsection_bytes);
            REQUIRE(subsection_equality(file_data_bytes_, subsection_bytes));
        }

        subsection_value = "1,9,2,3,0,22";
        subsection_bytes = get1PxJpeg(MARKER(0x00, 0x0E, /*v*/ 0x00, 0x03, 0x16, 0xB1));
        SECTION("Should write 1,9,2,3,0,22 (correcting for bounds) to data") {
            auto path = safeFileName(subsection_value);
            CAPTURE(path);
            copyBlankJpeg(path);

            REQUIRE(fs::exists(path));
            REQUIRE(fs::file_size(path) == jpegDataSz);

            jpeganno::JpegAnnotation::writeExpectedValues(path.generic_string(), toEightBitVec(subsection_value));

            const auto file_data_bytes_ = jpeganno::read(path.generic_string());
            CAPTURE(file_data_bytes_, subsection_bytes);
            REQUIRE(subsection_equality(file_data_bytes_, subsection_bytes));
        }

        subsection_value = "1,1,1,6,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,1,1,1,6,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5";
        subsection_bytes = get1PxJpeg(
                MARKER(0x00, 0x1E, /*v*/ 0x12, 0x48, 0x9C, 0x49, 0x24, 0x91, 0xB6, 0xDA, 0x09, 0xC4, 0x9B, 0x6D, 0x1B,
                       0x6D, 0xA4, 0x92, 0x00, 0xB6, 0xD9, 0x24));
        SECTION("Should write abnormally long sequence 1,1,1,6,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,1,1,1,6,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5 to data") {
            auto path = safeFileName(subsection_value);
            CAPTURE(path);
            copyBlankJpeg(path);

            REQUIRE(fs::exists(path));
            REQUIRE(fs::file_size(path) == jpegDataSz);

            jpeganno::JpegAnnotation::writeExpectedValues(path.generic_string(), toEightBitVec(subsection_value));

            const auto file_data_bytes_ = jpeganno::read(path.generic_string());
            CAPTURE(file_data_bytes_, subsection_bytes);
            REQUIRE(subsection_equality(file_data_bytes_, subsection_bytes));
        }
    }

    SECTION("Reading an image") {
        std::string subsection_value;
        std::vector<unsigned char> subsection_bytes;

        subsection_value = "1,2,3,4,5,6";
        subsection_bytes = get1PxJpeg(MARKER(0x00, 0x0E, /*v*/ 0x00, 0x03, 0x58, 0xD1));
        SECTION("Should parse 1,2,3,4,5,6 from data") {
            auto path = safeFileName("RIMG_"+subsection_value);
            CAPTURE(path);

            jpeganno::write(jpeganno::vectorToVecByte(subsection_bytes), path.generic_string());

            REQUIRE(fs::exists(path));
            REQUIRE(fs::file_size(path) == subsection_bytes.size());

            auto subsection_ints = toEightBitVec(subsection_value);
            auto parsed_ints____ = jpeganno::JpegAnnotation::parseExpectedValues(path.generic_string());

            CAPTURE(subsection_ints, parsed_ints____);
            REQUIRE(subsection_ints == parsed_ints____);
        }

        subsection_value = "6";
        subsection_bytes = get1PxJpeg(MARKER(0x00, 0x0E, /*v*/ 0x00, 0x00, 0x00, 0x06));
        SECTION("Should parse 6 from data") {
            auto path = safeFileName("RIMG_"+subsection_value);
            CAPTURE(path);

            jpeganno::write(jpeganno::vectorToVecByte(subsection_bytes), path.generic_string());

            REQUIRE(fs::exists(path));
            REQUIRE(fs::file_size(path) == subsection_bytes.size());

            auto subsection_ints = toEightBitVec(subsection_value);
            auto parsed_ints____ = jpeganno::JpegAnnotation::parseExpectedValues(path.generic_string());

            CAPTURE(subsection_ints, parsed_ints____);
            REQUIRE(subsection_ints == parsed_ints____);
        }

        subsection_value = "1,6,2,3,1,6";
        subsection_bytes = get1PxJpeg(MARKER(0x00, 0x0E, /*v*/ 0x00, 0x03, 0x16, 0xB1));
        SECTION("Should parse 1,9,2,3,0,22 (previously corrected for bounds) from data") {
            auto path = safeFileName("RIMG_"+subsection_value);
            CAPTURE(path);

            jpeganno::write(jpeganno::vectorToVecByte(subsection_bytes), path.generic_string());

            REQUIRE(fs::exists(path));
            REQUIRE(fs::file_size(path) == subsection_bytes.size());

            auto subsection_ints = toEightBitVec(subsection_value);
            auto parsed_ints____ = jpeganno::JpegAnnotation::parseExpectedValues(path.generic_string());

            CAPTURE(subsection_ints, parsed_ints____);
            REQUIRE(subsection_ints == parsed_ints____);
        }

        subsection_value = "1,1,1,6,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,1,1,1,6,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5";
        subsection_bytes = get1PxJpeg(
                MARKER(0x00, 0x1E, /*v*/ 0x12, 0x48, 0x9C, 0x49, 0x24, 0x91, 0xB6, 0xDA, 0x09, 0xC4, 0x9B, 0x6D, 0x1B,
                       0x6D, 0xA4, 0x92, 0x00, 0xB6, 0xD9, 0x24));
        SECTION("Should parse abnormally long sequence 1,1,1,6,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,1,1,1,6,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5 from data") {
            auto path = safeFileName("RIMG_"+subsection_value);
            CAPTURE(path);

            jpeganno::write(jpeganno::vectorToVecByte(subsection_bytes), path.generic_string());

            REQUIRE(fs::exists(path));
            REQUIRE(fs::file_size(path) == subsection_bytes.size());

            auto subsection_ints = toEightBitVec(subsection_value);
            auto parsed_ints____ = jpeganno::JpegAnnotation::parseExpectedValues(path.generic_string());

            CAPTURE(subsection_ints, parsed_ints____);
            REQUIRE(subsection_ints == parsed_ints____);
        }
    }
}

#endif //CVDICE_JPEGANNOTATION_TEST_H
