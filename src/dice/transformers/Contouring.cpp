//
// Created by Glenn R. Martin on 2019-05-10.
//

#include "Contouring.h"

#include <opencv2/opencv.hpp>
#include "../utils/hsv.h"

using namespace cv;
using namespace std;

constexpr unsigned int HIER_NEXT = 0;
constexpr unsigned int HIER_PREV = 1;
constexpr unsigned int HIER_1ST_CH = 2;
constexpr unsigned int HIER_PARENT = 3;

void cvdice::transformers::Contouring::performUpdate() {
    try {
        cv::Mat colorImage;

        cv::cvtColor(source_image, colorImage, cv::COLOR_GRAY2RGB, 3);

        RNG rng(12345);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        types::contours::Contours processedContours = {};

        findContours(source_image.clone(), contours, hierarchy, retr, approx+1, cv::Point(0, 0));

        colorImage.copyTo(display);

        int completeDepth = -1;

        std::function<int(int, int)> findDepth = [&hierarchy, &findDepth](int idx, int depth) {
            auto curr = hierarchy[idx];

            if (curr[HIER_PARENT] == -1) return depth;

            return findDepth(curr[HIER_PARENT], depth+1);
        };

        for (types::contours::Contours::size_type i = 0; i < contours.size(); i++) {
            auto moments = cv::moments(contours[i], true);
            auto contour = types::contours::Contour{
                STRUKEY(index) static_cast<int>(i),
                STRUKEY(points) contours[i],
                // `Point2d` is 2xDouble not 2-Dimension.
                STRUKEY(center) cv::Point2d(moments.m10 / moments.m00, moments.m01 / moments.m00),
                STRUKEY(moments) moments,
                STRUKEY(hierarchy) {
                    STRUKEY(depth) findDepth(i, 0),
                    STRUKEY(next) hierarchy[i][HIER_NEXT],
                    STRUKEY(previous) hierarchy[i][HIER_PREV],
                    STRUKEY(firstChild) hierarchy[i][HIER_1ST_CH],
                    STRUKEY(parent) hierarchy[i][HIER_PARENT]
                }
            };

            if (contour.hierarchy.depth > completeDepth) completeDepth = contour.hierarchy.depth;

            // printf("{\"i\": %d, \"next\": %d, \"prev\": %d, \"1stc\": %d, \"pare\": %d},\n", i, hierarchy[i].val[Next], hierarchy[i].val[Previous], hierarchy[i].val[FirstChild], hierarchy[i].val[Parent]);
            auto rgb = cvdice::hsv::hsvToRgb((contour.hierarchy.depth * 24) % 360, 100, 100);

            Scalar color = Scalar(rgb.r, rgb.g, rgb.b);
            drawContours(display, contours, i, color, 2, 8, hierarchy, 0, Point());

            processedContours.push_back(contour);
        }

        struct types::contours::DataListenerEvent evt = types::contours::DataListenerEvent{
            STRUKEY(depth) completeDepth,
            STRUKEY(contours) processedContours,
            STRUKEY(sourceImage) &display
        };

        this->arbitraryValues["types::contours::DataListenerEvent"] = std::make_pair(evt, this->receivedDataListener(evt));
    } catch (std::exception &e) {
        display = source_image.clone();
    }

    Xformer::update(display);
}

