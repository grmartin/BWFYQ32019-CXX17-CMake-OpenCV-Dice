//
// Created by Glenn R. Martin on 2019-05-16.
//

#include "Edger.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <utility>

#include "Colorer.h"
#include "../JpegFile.h"
#include "../../annotation/JpegAnnotation.h"

void cvdice::transformers::Edger::performUpdate() {
    try {
        cv::Mat blurry, detected_edges;
        blur(source_image.clone(), blurry, cv::Size(3, 3));
        Canny(blurry, detected_edges, threshold_value, threshold_value * ratio, calcKern(kernel_size));
        display = cv::Scalar::all(0);
        source_image.copyTo(display, detected_edges);
    } catch (std::exception &e) {
        UNUSED_REF(e);
        Xformer::update(source_image);
        return;
    }

    Xformer::update(display);
}
