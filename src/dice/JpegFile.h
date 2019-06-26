//
// Created by Glenn R. Martin on 2019-05-08.
//

#include <ostream>
#include <set>

#include <opencv2/core/mat.hpp>

#include "../annotation/JpegAnnotation.h"

#ifndef CVDICE_JPEGFILE_H
#define CVDICE_JPEGFILE_H

namespace cvdice {
    class JpegFile {
    public:
        std::multiset<uint8_t> expectedPips;
        cv::Mat matrix;

    private:
        JpegFile(std::ifstream& stream, const std::vector<uint8_t> &expectedPips);
        ~JpegFile();

    public:
        static JpegFile* fromFile(const fs::path& filePath);

        friend std::ostream &operator<<(std::ostream &os, const JpegFile &file);
    };
}

#endif //CVDICE_JPEGFILE_H
