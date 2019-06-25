//
// Created by Glenn R. Martin on 2019-06-24.
//

#ifndef CVDICE_IMAGEORIGIN_H
#define CVDICE_IMAGEORIGIN_H

#import "bases/Xformer.h"

namespace cvdice::transformers {
    class ImageOrigin : public Xformer {
        std::function<void(cv::Mat)> completionFunction;

    public:
        explicit ImageOrigin(cv::Mat& imageMatrix, bool pushImmediately = false);

        void push();

    private:
        void performUpdate() override;
    };
}

#endif //CVDICE_IMAGEORIGIN_H
