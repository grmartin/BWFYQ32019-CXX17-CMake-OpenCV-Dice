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

    inline VecByte& append(VecByte& target, VecByte from) {
        target.insert(target.end(), from.begin(), from.end());
        return target;
    }
}
#endif //CVDICE_VECBYTE_H
