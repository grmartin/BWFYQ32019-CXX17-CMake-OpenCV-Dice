//
// Created by Glenn R. Martin on 2019-05-14.
//

#include <opencv2/opencv.hpp>
#include "Xformer.h"
#include "XformerBase.h"

cvdice::transformers::Xformer::Xformer(const cv::Mat &sourceImage) {
    this->source_image = sourceImage.clone();
}

void cvdice::transformers::Xformer::update(const cv::Mat &updatedImage) {
    if (!has_built_ui) {
        has_built_ui = true;
        buildUi();
    }

    this->display = updatedImage.clone();

    if (chainTo) chainTo(updatedImage);
    else updateWindow(updatedImage);
}

void cvdice::transformers::Xformer::updateWindow(const cv::Mat &updatedImage) {
    imshow(window_name, updatedImage);
}

void cvdice::transformers::Xformer::showFor(const std::string &windowName) {
    this->window_name = windowName;
}

void cvdice::transformers::Xformer::chainAction(const cv::Mat &mat) {
    this->source_image = mat.clone();
    update();
}

void cvdice::transformers::Xformer::update() {
    if (enabled) performUpdate();
}

