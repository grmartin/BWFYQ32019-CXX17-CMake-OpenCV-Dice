//
// Created by Glenn R. Martin on 2019-05-16.
//

#ifndef CVDICE_EDGER_H
#define CVDICE_EDGER_H

#include "bases/Xformer.h"

namespace cvdice::transformers {
    class Edger : public Xformer {
        int ratio = 0;
        int threshold_value = 0;
        int max_ratio = 7;
        int max_threshold = 100;
        int kernel_size = 0; // must be between 3 and 7 and odd (3, 5, 7), `x = 3+(y*2)` see calcKern.

    public:
        explicit Edger() : Xformer() {};

        void performUpdate() override;

        void setRatio(int ratioVal) {
            ratio = ratioVal;
            this->update();
        }

        void setThresholdValue(int thresholdValue) {
            threshold_value = thresholdValue;
            this->update();
        }

        void setMaxThreshold(int maxThreshold) {
            max_threshold = maxThreshold;
            this->update();
        }

    private:
        static int calcKern(int sliderVal) {
            return (3+(sliderVal*2));
        }

    };
}

#endif //CVDICE_EDGER_H
