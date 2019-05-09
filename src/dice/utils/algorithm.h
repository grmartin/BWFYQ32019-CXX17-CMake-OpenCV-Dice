//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_ALGORITHM_H
#define CVDICE_ALGORITHM_H

#include <algorithm>
#include <vector>

namespace cvdice::algorithm {
    namespace loc {
        constexpr uint8_t first = 'f';
        constexpr uint8_t mid = 'm';
        constexpr uint8_t last = 'l';
    }

    template<class InputIterator, class BiaryFunction, typename ISz = std::size_t>
    BiaryFunction for_each_i(InputIterator first, InputIterator last, BiaryFunction fn) {
        for (ISz i = 0; first != last; ++first, i++)
            fn(*first, i);

        return fn;
    }

    template<class InputIterator, class BiaryFunction>
    BiaryFunction for_each_fl(InputIterator first, InputIterator last, BiaryFunction fn) {
        InputIterator _first = first;
        for (; first != last; ++first)
            fn(*first,
               first == _first ?
               loc::first : first+1 == last ?
                            loc::last : loc::mid);
        return fn;
    }
}

#endif //CVDICE_ALGORITHM_H
