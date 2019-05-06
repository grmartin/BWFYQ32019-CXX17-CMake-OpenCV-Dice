//
// Created by Glenn R. Martin on 2019-05-02.
//

#ifndef CVDICE_VECBYTE_H
#define CVDICE_VECBYTE_H

#include <vector>
#include <cstddef>
#include <cstdint>
#include <climits>

namespace jpeganno::vecbyte {
    typedef std::vector<std::byte> VecByte;

    template <typename T> VecByte structToVecByte(T structure) {
        std::vector<std::byte> vec;
        const uint8_t *ptr = (uint8_t *)&structure;
        const uint64_t sz = sizeof(structure);
        for(uint64_t i = 0; i < sz; i++) {
            vec.push_back(std::byte{ptr[i]});
        }
        return vec;
    }

    template<typename T> VecByte vectorToVecByte(std::vector<T> vector) {
        std::vector<std::byte> vec;
        vec.reserve(vector.size());
        std::for_each(
                vector.begin(),
                vector.end(),
                [&](T b){
                    vec.push_back(std::byte(b));
                }
        );
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

    inline void write(const VecByte& bytes, const std::string& path) {
        std::ofstream stream(path, std::ios::binary | std::ios::out | std::ios::trunc);
        stream.unsetf(std::ios::skipws);

        if (!stream.is_open()) return;

        std::for_each(bytes.begin(), bytes.end(), [&stream](std::byte byte) {
            char cbyte = static_cast<char>(byte);
            stream.write(&cbyte, 1);
        });

        stream.close();
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
