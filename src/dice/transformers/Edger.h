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
        int kernel_size = 0; // must be between 3 and 7 and odd (3, 5, 7), `x = 3+(y*2)` see calcKern.
        const int max_ratio = 7;
        const int max_threshold = 100;
        const int max_kernel_size = 2;

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

        void setKernelSize(int kernelSize) {
            kernel_size = kernelSize;
            this->update();
        }

        int getRatio() const {
            return ratio;
        }

        int getThresholdValue() const {
            return threshold_value;
        }

        int getKernelSize() const {
            return kernel_size;
        }

        int getMaxRatio() const {
            return max_ratio;
        }

        int getMaxThreshold() const {
            return max_threshold;
        }

        int getMaxKernelSize() const {
            return max_kernel_size;
        }

    private:
        static int calcKern(int sliderVal) {
            return (3+(sliderVal*2));
        }

    };
}

#endif //CVDICE_EDGER_H
