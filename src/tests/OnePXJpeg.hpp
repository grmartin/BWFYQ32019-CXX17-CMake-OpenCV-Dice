//
// Created by Glenn R. Martin on 2019-05-03.
//

#ifndef CVDICE_ONEPXJPEG_HPP
#define CVDICE_ONEPXJPEG_HPP

#include <cstddef>
#include <vector>

typedef unsigned char OnePXByteType;

#define b(n) static_cast<const OnePXByteType>(0x##n)

inline std::vector<OnePXByteType> get1PxJpeg(const std::vector<OnePXByteType>& bytes) {

    std::vector<OnePXByteType> returnValue = {
            b(FF), b(D8), b(FF), b(E0), b(00), b(10), b(4A), b(46), b(49), b(46), b(00), b(01), b(01), b(01), b(00),
            b(48), b(00), b(48), b(00), b(00), b(FF), b(DB), b(00), b(43), b(00), b(01), b(01), b(01), b(01), b(01),
            b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01),
            b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01),
            b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01),
            b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(01), b(FF),
            b(C0), b(00), b(0B), b(08), b(00), b(01), b(00), b(01), b(01), b(01), b(11), b(00), b(FF), b(C4), b(00),
            b(1F), b(00), b(00), b(01), b(05), b(01), b(01), b(01), b(01), b(01), b(01), b(00), b(00), b(00), b(00),
            b(00), b(00), b(00), b(00), b(01), b(02), b(03), b(04), b(05), b(06), b(07), b(08), b(09), b(0A), b(0B),
            b(FF), b(C4), b(00), b(B5), b(10), b(00), b(02), b(01), b(03), b(03), b(02), b(04), b(03), b(05), b(05),
            b(04), b(04), b(00), b(00), b(01), b(7D), b(01), b(02), b(03), b(00), b(04), b(11), b(05), b(12), b(21),
            b(31), b(41), b(06), b(13), b(51), b(61), b(07), b(22), b(71), b(14), b(32), b(81), b(91), b(A1), b(08),
            b(23), b(42), b(B1), b(C1), b(15), b(52), b(D1), b(F0), b(24), b(33), b(62), b(72), b(82), b(09), b(0A),
            b(16), b(17), b(18), b(19), b(1A), b(25), b(26), b(27), b(28), b(29), b(2A), b(34), b(35), b(36), b(37),
            b(38), b(39), b(3A), b(43), b(44), b(45), b(46), b(47), b(48), b(49), b(4A), b(53), b(54), b(55), b(56),
            b(57), b(58), b(59), b(5A), b(63), b(64), b(65), b(66), b(67), b(68), b(69), b(6A), b(73), b(74), b(75),
            b(76), b(77), b(78), b(79), b(7A), b(83), b(84), b(85), b(86), b(87), b(88), b(89), b(8A), b(92), b(93),
            b(94), b(95), b(96), b(97), b(98), b(99), b(9A), b(A2), b(A3), b(A4), b(A5), b(A6), b(A7), b(A8), b(A9),
            b(AA), b(B2), b(B3), b(B4), b(B5), b(B6), b(B7), b(B8), b(B9), b(BA), b(C2), b(C3), b(C4), b(C5), b(C6),
            b(C7), b(C8), b(C9), b(CA), b(D2), b(D3), b(D4), b(D5), b(D6), b(D7), b(D8), b(D9), b(DA), b(E1), b(E2),
            b(E3), b(E4), b(E5), b(E6), b(E7), b(E8), b(E9), b(EA), b(F1), b(F2), b(F3), b(F4), b(F5), b(F6), b(F7),
            b(F8), b(F9), b(FA), b(FF), b(DA), b(00), b(08), b(01), b(01), b(00), b(00), b(3F), b(00), b(FE), b(FE),
            b(2B), b(FF), b(D9)
    };

    if (!bytes.empty()) {
        returnValue.insert(returnValue.end()-2, bytes.begin(), bytes.end());
    }

    return returnValue;
}

#undef b

#endif //CVDICE_ONEPXJPEG_HPP
