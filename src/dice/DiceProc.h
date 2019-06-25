//
// Created by Glenn R. Martin on 2019-06-25.
//

#ifndef CVDICE_DICEPROC_H
#define CVDICE_DICEPROC_H

#include <set>
#include "JpegFile.h"

namespace cvdice {
    namespace classification {
        enum RoughShape {
            Square,
            Circle,
            Else
        };
    }

    struct BasicConfig {
        int colorerValue;
        int thresholderType;
        int thresholderValue;
        int contourMode;
        int contourApproximation;
        double epsilonDeviationDetectionPoly;
    };

    class DiceProc {
    public:
        static std::multiset<uint8_t> getBasicDicePips(cvdice::JpegFile *jpeg, struct BasicConfig config);
    };
}


#endif //CVDICE_DICEPROC_H
