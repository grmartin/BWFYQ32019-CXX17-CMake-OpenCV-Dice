//
// Created by Glenn R. Martin on 2019-05-14.
//

#ifndef CVDICE_XFORMER_H
#define CVDICE_XFORMER_H

#import <opencv2/core/mat.hpp>

namespace cvdice::transformers {


    class Xformer {
    protected:
        cv::Mat source_image;
        cv::Mat display;

        std::string window_name;
        std::vector<int> validValues;

        bool has_built_ui = false;

        explicit Xformer(const cv::Mat &sourceImage);

        virtual void buildUi() = 0;

        virtual void update(const cv::Mat &updatedImage);

        virtual void updateWindow(const cv::Mat &mat);

    public:
        std::function<void(cv::Mat)> chainTo;

        void showFor(const std::string &windowName);

        virtual void performUpdate() = 0;

        virtual void update() final;

        virtual void chainAction(const cv::Mat &mat);

        bool enabled = true;
    };


}

#endif //CVDICE_XFORMER_H
