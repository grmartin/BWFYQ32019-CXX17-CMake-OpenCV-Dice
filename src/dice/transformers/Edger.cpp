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

#ifdef CVD_USE_QT5
static QString KernSzName = QString::fromLocal8Bit("KernSz");
static QString ThreshValueName = QString::fromLocal8Bit("Thresh Value");
static QString RatioName = QString::fromLocal8Bit("Ratio");
#endif

void cvdice::transformers::Edger::buildUi() {
#ifdef CVD_USE_QT5
    if (this->appender == nullptr) return;
    CVQTImageToolbar *toolbar1 = new CVQTImageToolbar("Canny Kern:", 0, 0, 2, this->enabled);
    CVQTImageToolbar *toolbar2 = new CVQTImageToolbar("Canny Thresh Value:", threshold_value, 0, max_threshold, this->enabled);
    CVQTImageToolbar *toolbar3 = new CVQTImageToolbar("Canny Ratio:", ratio, 0, max_ratio, this->enabled);

    toolbar2->hideEnabled();
    toolbar3->hideEnabled();

    toolbar1->setObjectName(KernSzName);
    toolbar2->setObjectName(ThreshValueName);
    toolbar3->setObjectName(RatioName);

    toolbar1->setDelegate(this);
    toolbar2->setDelegate(this);
    toolbar3->setDelegate(this);

    auto pairs =
        std::make_tuple(this->appender(toolbar1), this->appender(toolbar2), this->appender(toolbar3));
    this->opaqueUiHandle = &pairs;
#else
    auto selfUpdater = [](int pos, void *self) { reinterpret_cast<Edger *>(self)->update(); };
    cv::createTrackbar("Canny Kern:",
                       window_name, &kernel_size,
                       2, selfUpdater, reinterpret_cast<void *>(this));
    cv::createTrackbar("Canny Thresh Value: ",
                       window_name, &threshold_value,
                       max_threshold, selfUpdater, reinterpret_cast<void *>(this));
    cv::createTrackbar("Canny Ratio: ",
                       window_name, &ratio,
                       max_ratio, selfUpdater, reinterpret_cast<void *>(this));
#endif
}

void cvdice::transformers::Edger::performUpdate() {
    try {
        cv::Mat blurry, detected_edges;
        blur(source_image, blurry, cv::Size(3, 3));
        Canny(blurry, detected_edges, threshold_value, threshold_value * ratio, calcKern(kernel_size));
        display = cv::Scalar::all(0);
        source_image.copyTo(display, detected_edges);
    } catch (std::exception &e) {
        XformerBase::update(source_image);
        return;
    }

    XformerBase::update(display);
}

#ifdef CVD_USE_QT5

void cvdice::transformers::Edger::imageToolbarChanged(CVQTImageToolbar *toolbar, int changedValue) {
    if (toolbar->objectName() == KernSzName) {
        if (changedValue == kernel_size) return;
        kernel_size = changedValue;
    } else if (toolbar->objectName() == ThreshValueName) {
        if (changedValue == threshold_value) return;
        threshold_value = changedValue;
    } else if (toolbar->objectName() == RatioName) {
        if (changedValue == ratio) return;
        ratio = changedValue;
    }

    this->update();
}

#endif
