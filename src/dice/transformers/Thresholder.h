//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_THRESHOLDER_H
#define CVDICE_THRESHOLDER_H

#import "XformerBase.h"

namespace cvdice::transformers {
    class Thresholder : public XformerBase {
        int threshold_value = 0;
        int threshold_type = 3;

        int const max_value = 255;
        int const max_type = 4;
        int const max_binary_value = 255;

    public:
        explicit Thresholder(const cv::Mat &sourceImage) : XformerBase(sourceImage) {}

        void update() override;

    private:
        void buildUi() override;

    };
}
#endif //CVDICE_THRESHOLDER_H
