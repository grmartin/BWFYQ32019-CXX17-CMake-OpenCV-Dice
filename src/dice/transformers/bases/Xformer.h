//
// Created by Glenn R. Martin on 2019-05-14.
//

#ifndef CVDICE_XFORMER_H
#define CVDICE_XFORMER_H

#import <opencv2/core/mat.hpp>

#define CHAIN_XFORMER(first, second) first->chainTo = [&second](cv::Mat mat) { second->chainAction(mat); }

namespace cvdice::transformers {

    class Xformer {
    protected:
        cv::Mat source_image;
        cv::Mat display;

        bool has_built_ui = false;

        explicit Xformer();

        virtual void update(const cv::Mat& updatedImage);

    public:
        std::function<void(cv::Mat)> chainTo; // = nullptr;

        virtual void performUpdate() = 0;

        virtual void update() final;

        virtual void chainAction(const cv::Mat& mat);

        bool enabled = true;

        std::function<void(Xformer* transformer)> buildUi = [](Xformer* ignored){};
        std::function<void(Xformer* transformer, const cv::Mat& mat)> updateWindow = [](Xformer* ignored1, const cv::Mat& ignored2){};
    };


}

#endif //CVDICE_XFORMER_H
