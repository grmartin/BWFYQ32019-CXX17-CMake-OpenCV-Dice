//
// Created by Glenn R. Martin on 2019-05-09.
//

#include <opencv2/opencv.hpp>
#include "XformerBase.h"

cvdice::transformers::XformerBase::XformerBase(const cv::Mat &sourceImage) {
    this->source_image = sourceImage.clone();
}

void cvdice::transformers::XformerBase::update(const cv::Mat &updatedImage) {
    if (!has_built_ui) {
        has_built_ui = true;
        buildUi();
    }

    this->display = updatedImage.clone();

    if (chainTo) chainTo(updatedImage);
    else imshow(window_name, updatedImage);
}

void cvdice::transformers::XformerBase::showFor(const std::string &windowName) {
    this->window_name = windowName;
}

void cvdice::transformers::XformerBase::chainAction(const cv::Mat &mat) {
    this->source_image = mat.clone();
    update();
}

void cvdice::transformers::XformerBase::update() {
    if (enabled) performUpdate();
}
