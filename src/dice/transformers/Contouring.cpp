//
// Created by Glenn R. Martin on 2019-05-10.
//

#include "Contouring.h"

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void cvdice::transformers::Contouring::performUpdate() {
    try {
        RNG rng(12345);
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        findContours(source_image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

        /// Draw contours
        Mat drawing = Mat::zeros(source_image.size(), CV_8UC3);
        for (int i = 0; i < contours.size(); i++) {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            drawContours(display, contours, i, color, 2, 8, hierarchy, 0, Point());
        }
    } catch (std::exception e) {
        XformerBase::update(source_image);
        return;
    }

    XformerBase::update(display);
}

void cvdice::transformers::Contouring::buildUi() {

}
