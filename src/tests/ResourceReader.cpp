//
// Created by Glenn R. Martin on 2019-05-08.
//

#include <fstream>
#include <algorithm>
#include "ResourceReader.h"

static RawByteVector loadResource(const std::string &resourceFileName) {
    RawByteVector vec;

    std::ifstream file(resourceFileName, std::ios::binary | std::ios::ate);
    file.unsetf(std::ios::skipws);

    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    if (fileSize > 0) {
        vec.reserve((unsigned)fileSize);
    }
    std::for_each(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>(),
            [&vec](char b) { vec.push_back(b); });

    return vec;
}

RawByteVector ResourceReader::getBytes(const std::string &resourceFileName) {
    if (this->cache.find(resourceFileName) == this->cache.end()) {
        this->cache[resourceFileName] = loadResource(resourceFileName);
    }
    return RawByteVector(this->cache[resourceFileName]);
}

RawByteVector ResourceReader::getJpegMarkedBytes(const std::string &resourceFileName, const RawByteVector &bytes) {
    RawByteVector vec = RawByteVector(this->getBytes(resourceFileName));

    if (!bytes.empty()) {
        vec.insert(vec.end() - 2, bytes.begin(), bytes.end());
    }

    return vec;
}