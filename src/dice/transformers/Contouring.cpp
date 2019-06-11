//
// Created by Glenn R. Martin on 2019-05-10.
//

#include "Contouring.h"

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#ifdef CVD_USE_QT5
#include "../ui/CVQTTag.h"

static QString RetrievalModeName = QString::fromLocal8Bit("Retr");
static QString ApproxModeName = QString::fromLocal8Bit("Approx");
#endif

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

        // make source colorful.

        cv::Mat colorImage;

        cv::cvtColor(source_image, colorImage, cv::COLOR_GRAY2RGB, 3);

        RNG rng(12345);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        findContours(source_image.clone(), contours, hierarchy, retr, approx+1, cv::Point(0, 0));

        colorImage.copyTo(display);

        for (int i = 0; i < contours.size(); i++) {
            int colorI = i * 3;
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            drawContours(display, contours, i, color, 2, 8, hierarchy, 0, Point());
        }
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
