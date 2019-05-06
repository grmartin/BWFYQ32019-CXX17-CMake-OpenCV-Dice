//
// Created by Glenn R. Martin on 2019-05-02.
//

#ifndef CVDICE_CHUNK_H
#define CVDICE_CHUNK_H

#include <vector>
#include <ctgmath>
#include <cstddef>

namespace jpeganno::util::chunk {
    template<typename Iterator>
    void for_each_interval(Iterator begin, Iterator end, size_t interval_size,
                           std::function<void(Iterator, Iterator)> operation) {
        auto to = begin;

        while (to != end) {
            auto from = to;

            auto counter = interval_size;
            while (counter > 0 && to != end) {
                ++to;
                --counter;
            }

            operation(from, to);
        }
    }

    template<typename T>
    std::vector<std::vector<T>> chunk(std::vector<T> vector, size_t interval_size) {
        std::vector<std::vector<T>> out;

        if (interval_size == 0) {
            return out;
        }

        out.reserve(vector.size() / interval_size + 1);
        typedef decltype(vector.begin()) it_t;
        for_each_interval<it_t>(
                vector.begin(),
                vector.end(),
                interval_size,
                [&out, interval_size](it_t from, it_t to) {
                    std::vector<T> inner;
                    inner.reserve(interval_size);
                    std::for_each(from, to, [&inner](T val) { inner.push_back(val); });
                    out.push_back(inner);
                });
        return out;
    }
}
#endif //CVDICE_CHUNK_H
