#include <utility>

//
// Created by Glenn R. Martin on 4/29/2019.
//

#include <cstdint>
#include <vector>

#if CVD_USE_BOOST_FS == 1
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

#ifndef CVDICE_JPEGANNOTATION_H
#define CVDICE_JPEGANNOTATION_H


namespace jpeganno {
	class JpegAnnotation {
	public:
		/**
		 * Read the expected values from a JPEG file, if they exist.
		 * @param jpegFilePath
		 * @return
		 */
		static std::vector<uint8_t> parseExpectedValues(const fs::path& jpegFilePath);

		/**
		 * Write our expected values to a JPEG file encoding the information in to an APPn Block
		 * @param jpegFilePath
		 * @param expectations
		 */
		static void writeExpectedValues(const fs::path& jpegFilePath, const std::vector<uint8_t>& expectations);

		/**
		 * Determine if the JPEG at a given path has our expected values block within it.
		 * @param jpegFilePath
		 * @return
		 */
		static bool hasExpectedValuesBlock(const fs::path& jpegFilePath) {
			return !parseExpectedValues(jpegFilePath).empty();
		}
	};
}
#endif //CVDICE_JPEGANNOTATION_H
