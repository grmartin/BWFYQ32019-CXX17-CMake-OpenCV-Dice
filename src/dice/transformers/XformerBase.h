//
// Created by Glenn R. Martin on 2019-05-09.
//


#import <opencv2/core/mat.hpp>

#ifndef CVDICE_XFORMERBASE_H
#define CVDICE_XFORMERBASE_H

#define CHAIN_XFORMER(first, second) first->chainTo = [&second](Mat mat) { second->chainAction(mat); }

namespace cvdice::transformers {
    class XformerBase {
    protected:
        cv::Mat source_image;
        cv::Mat display;

        std::string window_name;
        std::vector<int> validValues;

        bool has_built_ui = false;

        explicit XformerBase(const cv::Mat &sourceImage);
        virtual void buildUi() = 0;
        virtual void update(const cv::Mat &updatedImage);

    public:
        std::function<void(cv::Mat)> chainTo;
        void showFor(const std::string &windowName);
        virtual void update() = 0;
        virtual void chainAction(const cv::Mat &mat);
    };
}
#endif //CVDICE_XFORMERBASE_H
