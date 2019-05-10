//
// Created by Glenn R. Martin on 2019-05-09.
//

#include "Colorer.h"
#include "XformerBase.h"
#include "../JpegFile.h"
#include "../../annotation/JpegAnnotation.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <utility>
#include "Thresholder.h"

void cvdice::transformers::Thresholder::buildUi() {
    auto selfUpdater = [](int pos, void *self) { reinterpret_cast<Thresholder *>(self)->update(); };
    cv::createTrackbar("Thresh Type:",
                       window_name, &threshold_type,
                       max_type, selfUpdater, reinterpret_cast<void *>(this));
    cv::createTrackbar("Thresh Value: ",
                       window_name, &threshold_value,
                       max_value, selfUpdater, reinterpret_cast<void *>(this));
}

void cvdice::transformers::Thresholder::performUpdate() {
    std::cout << "Thresh Type: " << threshold_type << ", Value: " << threshold_value << std::endl;

    threshold(source_image, display, threshold_value, max_binary_value, threshold_type);
    XformerBase::update(display);
}
