//
// Created by Glenn R. Martin on 2019-05-09.
//

#include "Thresholder.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <utility>

#include "Colorer.h"
#include "../JpegFile.h"
#include "../../annotation/JpegAnnotation.h"

#ifdef CVD_USE_QT5
static QString ThreshTypeName = QString::fromLocal8Bit("Thresh Type");
static QString ThreshValueName = QString::fromLocal8Bit("Thresh Value");
#endif

void cvdice::transformers::Thresholder::buildUi() {
#ifdef CVD_USE_QT5
    if (this->appender == nullptr) return;
    CVQTImageToolbar *toolbar1 = new CVQTImageToolbar("Thresh Type:", threshold_type, 0, max_type, this->enabled);
    CVQTImageToolbar *toolbar2 = new CVQTImageToolbar("Thresh Value:", threshold_value, 0, max_value, this->enabled);

    toolbar2->hideEnabled();

    toolbar1->setObjectName(ThreshTypeName);
    toolbar2->setObjectName(ThreshValueName);

    toolbar1->setDelegate(this);
    toolbar2->setDelegate(this);

    auto pairs =
        std::make_tuple(this->appender(toolbar1), this->appender(toolbar2));
    this->opaqueUiHandle = &pairs;
#else
    auto selfUpdater = [](int pos, void *self) { reinterpret_cast<Thresholder *>(self)->update(); };
    cv::createTrackbar("Thresh Type:",
                       window_name, &threshold_type,
                       max_type, selfUpdater, reinterpret_cast<void *>(this));
    cv::createTrackbar("Thresh Value: ",
                       window_name, &threshold_value,
                       max_value, selfUpdater, reinterpret_cast<void *>(this));
#endif
}

void cvdice::transformers::Thresholder::performUpdate() {
    std::cout << "Thresh Type: " << threshold_type << ", Value: " << threshold_value << std::endl;

    threshold(source_image, display, threshold_value, max_binary_value, threshold_type);
    XformerBase::update(display);
}

#ifdef CVD_USE_QT5

void cvdice::transformers::Thresholder::imageToolbarChanged(CVQTImageToolbar *toolbar, int changedValue) {
    if (toolbar->objectName() == ThreshTypeName) {
        if (changedValue == threshold_type) return;
        threshold_type = changedValue;
    } else if (toolbar->objectName() == ThreshValueName) {
        if (changedValue == threshold_value) return;
        threshold_value = changedValue;
    }

    this->update();
}

#endif
