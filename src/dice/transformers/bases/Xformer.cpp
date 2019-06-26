//
// Created by Glenn R. Martin on 2019-05-14.
//

#include <opencv2/opencv.hpp>
#include "Xformer.h"

cvdice::transformers::Xformer::Xformer() : Identifiable() {};

void cvdice::transformers::Xformer::update(const cv::Mat &updatedImage) {
    if (!has_built_ui) {
        has_built_ui = true;
        buildUi(this);
    }

    this->display = updatedImage.clone();

    if (chainTo) chainTo(this, updatedImage.clone());
    else updateWindow(this, updatedImage);
}

void cvdice::transformers::Xformer::chainAction(const cv::Mat &mat) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    this->source_image = mat.clone();
    update();
}

void cvdice::transformers::Xformer::update() {
    if (enabled) {
        performUpdate();
    } else {
        display = source_image.clone();
        update(display);
    }
}

