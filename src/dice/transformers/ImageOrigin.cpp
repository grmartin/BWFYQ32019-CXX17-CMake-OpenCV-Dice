//
// Created by Glenn R. Martin on 2019-06-24.
//

#include "ImageOrigin.h"

cvdice::transformers::ImageOrigin::ImageOrigin(cv::Mat &imageMatrix, bool pushImmediately) : XformerBase() {
    this->source_image = imageMatrix.clone();

    if (pushImmediately)
        this->push();
}

void cvdice::transformers::ImageOrigin::push() {
    this->update(this->source_image.clone());
}

void cvdice::transformers::ImageOrigin::buildUi() {}

void cvdice::transformers::ImageOrigin::performUpdate() {}
