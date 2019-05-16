//
// Created by Glenn R. Martin on 2019-05-16.
//

#ifndef CVDICE_EDGER_H
#define CVDICE_EDGER_H


#import "bases/XformerBase.h"

namespace cvdice::transformers {
    class Edger : public XformerBase {
        int ratio = 0;
        int threshold_value = 0;
        int max_ratio = 7;
        int max_threshold = 100;
        int kernel_size = 0; // must be between 3 and 7 and odd (3, 5, 7), `x = 3+(y*2)` see calcKern.

    public:
        explicit Edger(const cv::Mat &sourceImage) : XformerBase(sourceImage) {};

        void performUpdate() override;

    private:
        void buildUi() override;

        static int calcKern(int sliderVal) {
            return (3+(sliderVal*2));
        }

#ifdef CVD_USE_QT5
        void imageToolbarChanged(CVQTImageToolbar *toolbar, int value) override;
#endif
    };
}

#endif //CVDICE_EDGER_H
