//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_THRESHOLDER_H
#define CVDICE_THRESHOLDER_H

#include <opencv2/imgproc.hpp>
#include "bases/Xformer.h"

namespace cvdice::transformers {
    class Thresholder : public Xformer {
        int type = cv::ThresholdTypes::THRESH_TOZERO;
        int value = 0;

        int const max_type = 4;
        int const max_value = 255;
        int const max_binary_value = 255;

    public:
        explicit Thresholder(int type = cv::ThresholdTypes::THRESH_TOZERO, int value = 0) : Xformer() {
            this->value = value;
            this->type = type;
        }

        void performUpdate() override;

        void setType(int typeVal) {
            type = typeVal;
            this->update();
        }

        void setValue(int valueVal) {
            value = valueVal;
            this->update();
        }
    };
}
#endif //CVDICE_THRESHOLDER_H
