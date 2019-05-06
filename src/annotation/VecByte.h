//
// Created by Glenn R. Martin on 2019-05-02.
//

#ifndef CVDICE_VECBYTE_H
#define CVDICE_VECBYTE_H

#include <vector>
#include <cstddef>
#include <cstdint>
#include <climits>

namespace jpeganno {
    typedef std::vector<std::byte> VecByte;

    template <typename T> VecByte toVecByte(T structure) {
        std::vector<std::byte> vec;
        const uint8_t *ptr = (uint8_t *)&structure;
        const uint64_t sz = sizeof(structure);
        for(uint64_t i = 0; i < sz; i++) {
            vec.push_back(std::byte{ptr[i]});
        }
        return vec;
    }

    template<typename T>
    inline std::byte getAStreamByte(T &stream) {
        char cbyte = 0;
        stream.read(&cbyte, 1);
        return std::byte(cbyte);
    }

    inline VecByte& append(VecByte& target, VecByte from) {
        target.insert(target.end(), from.begin(), from.end());
        return target;
    }

    inline VecByte read(const std::string& path) {
        VecByte vec;

        std::ifstream file(path, std::ios::binary | std::ios::ate);
        file.unsetf(std::ios::skipws);

        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        vec.reserve(fileSize);
        std::for_each(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>(),
            [&vec](char b){ vec.push_back(std::byte(b)); });

        return vec;
    }
}
#endif //CVDICE_VECBYTE_H
