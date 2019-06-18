//
// Created by Glenn R. Martin on 2019-05-10.
//

#include "Contouring.h"

#include <opencv2/opencv.hpp>
#include "../utils/hsv.h"

using namespace cv;
using namespace std;

#ifdef CVD_USE_QT5
#include "../ui/CVQTTag.h"

static QString RetrievalModeName = QString::fromLocal8Bit("Retr");
static QString ApproxModeName = QString::fromLocal8Bit("Approx");
#endif

constexpr unsigned int HIER_NEXT = 0;
constexpr unsigned int HIER_PREV = 1;
constexpr unsigned int HIER_1ST_CH = 2;
constexpr unsigned int HIER_PARENT = 3;

void cvdice::transformers::Contouring::buildUi() {
#ifdef CVD_USE_QT5
    if (this->appender == nullptr) return;
    CVQTImageToolbar *toolbar1 = new CVQTImageToolbar("Retrieval Mode:", retr, 0, max_retr, this->enabled);
    CVQTImageToolbar *toolbar2 = new CVQTImageToolbar("Approx Type:", approx, 0, max_approx, this->enabled);

    toolbar2->hideEnabled();

    setInternalContextName(toolbar1, RetrievalModeName);
    setInternalContextName(toolbar2, ApproxModeName);

    toolbar1->setDelegate(this);
    toolbar2->setDelegate(this);

    auto pairs =
        std::make_tuple(this->appender(toolbar1), this->appender(toolbar2));
    this->opaqueUiHandle = &pairs;
#endif
}

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

        for (int i = 0; i < contours.size(); i++) {
            auto moments = cv::moments(contours[i], true);
            auto contour = types::contours::Contour{
                .index = i,
                .points =  contours[i],
                .moments = moments,
                // `Point2d` is 2xDouble not 2-Dimension.
                .center = cv::Point2d(moments.m10 / moments.m00, moments.m01 / moments.m00),
                .hierarchy = {
                    .depth = findDepth(i, 0),
                    .next = hierarchy[i][HIER_NEXT],
                    .previous = hierarchy[i][HIER_PREV],
                    .firstChild = hierarchy[i][HIER_1ST_CH],
                    .parent = hierarchy[i][HIER_PARENT]
                }
            };

            if (contour.hierarchy.depth > completeDepth) completeDepth = contour.hierarchy.depth;

            // printf("{\"i\": %d, \"next\": %d, \"prev\": %d, \"1stc\": %d, \"pare\": %d},\n", i, hierarchy[i].val[Next], hierarchy[i].val[Previous], hierarchy[i].val[FirstChild], hierarchy[i].val[Parent]);
            auto rgb = cvdice::hsv::hsvToRgb((contour.hierarchy.depth * 24) % 360, 100, 100);

            Scalar color = Scalar(rgb.r, rgb.g, rgb.b);
            drawContours(display, contours, i, color, 2, 8, hierarchy, 0, Point());

            processedContours.push_back(contour);
        }

        this->receivedDataListener(types::contours::DataListenerEvent{
            .depth = completeDepth,
            .contours = processedContours,
            .sourceImage = &display
        });
    } catch (std::exception &e) {
        display = source_image.clone();
    }

    XformerBase::update(display);
}

#ifdef CVD_USE_QT5

void cvdice::transformers::Contouring::imageToolbarChanged(CVQTImageToolbar *toolbar, int changedValue) {
    if (getInternalContextName(toolbar) == RetrievalModeName) {
        if (changedValue == retr) return;
        retr = changedValue;
        toolbar->setValueLabel(QString::number(changedValue));
    } else if (getInternalContextName(toolbar) == ApproxModeName) {
        if (changedValue == approx) return;
        approx = changedValue;
        toolbar->setValueLabel(QString::number(changedValue));
    }

    this->update();
}

#endif
