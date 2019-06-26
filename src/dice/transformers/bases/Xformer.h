//
// Created by Glenn R. Martin on 2019-05-14.
//

#ifndef CVDICE_XFORMER_H
#define CVDICE_XFORMER_H

#include "Identifiable.h"

#include <functional>

#include <opencv2/core/mat.hpp>

#define CHAIN_XFORMER(first, second) first->chainTo = [&second](cvdice::transformers::Identifiable* inputXformer, cv::Mat mat) { \
    second->arbitraryValues.insert(inputXformer->arbitraryValues.begin(), inputXformer->arbitraryValues.end()); \
    second->chainAction(mat); \
}

namespace cvdice::transformers {

    class Xformer : public Identifiable {
    protected:
        cv::Mat source_image;
        cv::Mat display;

        bool has_built_ui = false;

        explicit Xformer();

        virtual void update(const cv::Mat& updatedImage);

    public:
        std::function<void(cvdice::transformers::Identifiable*, cv::Mat)> chainTo; // = nullptr;

        virtual void performUpdate() = 0;

        virtual void update() final;

        virtual void chainAction(const cv::Mat& mat);

        bool enabled = true;

        std::function<void(Xformer* transformer)> buildUi = [](Xformer* ignored){};
        std::function<void(Xformer* transformer, const cv::Mat& mat)> updateWindow = [](Xformer* ignored1, const cv::Mat& ignored2){};
    };


}

#endif //CVDICE_XFORMER_H
