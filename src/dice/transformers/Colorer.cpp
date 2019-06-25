//
// Created by Glenn R. Martin on 2019-05-09.
//

#include "Colorer.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <utility>

#include "bases/Xformer.h"
#include "../JpegFile.h"
#include "../../annotation/JpegAnnotation.h"

cvdice::transformers::Colorer::Colorer(int value) : Xformer() {
    this->validValues = {
        //cv::COLOR_BGR2BGRA, cv::COLOR_BGRA2BGR, cv::COLOR_BGR2RGBA, cv::COLOR_RGBA2BGR, cv::COLOR_BGR2RGB, cv::COLOR_BGRA2RGBA,
        cv::COLOR_BGR2GRAY, cv::COLOR_RGB2GRAY,
//        cv::COLOR_BGR2XYZ, cv::COLOR_RGB2XYZ, cv::COLOR_XYZ2BGR, cv::COLOR_XYZ2RGB,
//        cv::COLOR_BGR2YCrCb, cv::COLOR_RGB2YCrCb, cv::COLOR_YCrCb2BGR, cv::COLOR_YCrCb2RGB,
//        cv::COLOR_BGR2HSV, cv::COLOR_RGB2HSV,
//        cv::COLOR_BGR2Lab, cv::COLOR_RGB2Lab,
//        cv::COLOR_BGR2Luv, cv::COLOR_RGB2Luv, cv::COLOR_BGR2HLS, cv::COLOR_RGB2HLS,
//        cv::COLOR_HSV2BGR, cv::COLOR_HSV2RGB,
//        cv::COLOR_Lab2BGR, cv::COLOR_Lab2RGB, cv::COLOR_Luv2BGR, cv::COLOR_Luv2RGB, cv::COLOR_HLS2BGR, cv::COLOR_HLS2RGB,
//        cv::COLOR_BGR2HSV_FULL, cv::COLOR_RGB2HSV_FULL, cv::COLOR_BGR2HLS_FULL, cv::COLOR_RGB2HLS_FULL,
//        cv::COLOR_HSV2BGR_FULL, cv::COLOR_HSV2RGB_FULL, cv::COLOR_HLS2BGR_FULL, cv::COLOR_HLS2RGB_FULL,
//        cv::COLOR_LBGR2Lab, cv::COLOR_LRGB2Lab, cv::COLOR_LBGR2Luv, cv::COLOR_LRGB2Luv,
//        cv::COLOR_Lab2LBGR, cv::COLOR_Lab2LRGB, cv::COLOR_Luv2LBGR, cv::COLOR_Luv2LRGB,
//        cv::COLOR_BGR2YUV, cv::COLOR_RGB2YUV, cv::COLOR_YUV2BGR, cv::COLOR_YUV2RGB,
    };
    this->value = value;
}

void cvdice::transformers::Colorer::performUpdate() {
    if (value >= 0) {
        std::cout << "Color Conversion: [" << value << "]=" << this->validValues[value] << std::endl;
        try {
            cv::cvtColor(source_image.clone(), display, this->validValues[value], 3);
        } catch (cv::Exception &ignored) { return; }
    }

    Xformer::update(display);
}
