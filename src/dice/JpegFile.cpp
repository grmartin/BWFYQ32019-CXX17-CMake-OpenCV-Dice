//
// Created by Glenn R. Martin on 2019-05-08.
//

#include <opencv2/opencv.hpp>

#include "JpegFile.h"
#include "../annotation/Defer.h"
#include "utils/algorithm.h"


cvdice::JpegFile* cvdice::JpegFile::fromFile(const fs::path& filePath) {
    const auto values = jpeganno::JpegAnnotation::parseExpectedValues(filePath);
    std::ifstream stream(filePath.generic_string(), std::ios::binary | std::ios::in | std::ios::ate);
    stream.unsetf(std::ios::skipws);

    return new JpegFile(stream, values);
}

cvdice::JpegFile::JpegFile(std::ifstream &stream, const std::vector<uint8_t> &expectedPips) {
    this->expectedPips = std::multiset<uint8_t>(expectedPips.begin(), expectedPips.end());

    const auto streamSize = stream.tellg();
    stream.seekg(stream.beg);

    std::vector<char> data;
    //data.reserve(streamSize);

    std::copy(std::istream_iterator<char>(stream), std::istream_iterator<char>(), std::back_inserter(data));
    this->matrix = cv::imdecode(cv::Mat(data), cv::IMREAD_UNCHANGED);
}

std::ostream &cvdice::operator<<(std::ostream &os, const cvdice::JpegFile &file) {
    auto values = file.expectedPips;

    os << "matrix: " << file.matrix.type() <<"/" << file.matrix.total() << ", expectedPips: |";

    algorithm::for_each_i(values.begin(), values.end(), [&os](uint8_t value, auto i){
        i == 0 ? (os << static_cast<unsigned>(value)) : (os << "," << static_cast<unsigned>(value));
    });

    os << "|" << std::endl;

    return os;
}

cvdice::JpegFile::~JpegFile() {
    this->matrix.empty();
}
