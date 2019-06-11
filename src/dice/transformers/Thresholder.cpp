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
#include "../ui/CVQTTag.h"

static QString ThreshTypeName = QString::fromLocal8Bit("Thresh Type");
static QString ThreshValueName = QString::fromLocal8Bit("Thresh Value");
#endif

void cvdice::transformers::Thresholder::buildUi() {
#ifdef CVD_USE_QT5
    if (this->appender == nullptr) return;
    CVQTImageToolbar *toolbar1 = new CVQTImageToolbar("Thresh Type:", type, 0, max_type, this->enabled);
    CVQTImageToolbar *toolbar2 = new CVQTImageToolbar("Thresh Value:", value, 0, max_value, this->enabled);

    toolbar2->hideEnabled();

    setInternalContextName(toolbar1, ThreshTypeName);
    setInternalContextName(toolbar2, ThreshValueName);

    toolbar1->setDelegate(this);
    toolbar2->setDelegate(this);

    auto pairs =
        std::make_tuple(this->appender(toolbar1), this->appender(toolbar2));
    this->opaqueUiHandle = &pairs;
#endif
}

void cvdice::transformers::Thresholder::performUpdate() {
    std::cout << "Thresh Type: " << type << ", Value: " << value << std::endl;

    threshold(source_image.clone(), display, value, max_binary_value, type);
    XformerBase::update(display);
}

#ifdef CVD_USE_QT5

void cvdice::transformers::Thresholder::imageToolbarChanged(CVQTImageToolbar *toolbar, int changedValue) {
    if (getInternalContextName(toolbar) == ThreshTypeName) {
        if (changedValue == type) return;
        type = changedValue;
        toolbar->setValueLabel(QString::number(changedValue));
    } else if (getInternalContextName(toolbar) == ThreshValueName) {
        if (changedValue == value) return;
        value = changedValue;
        toolbar->setValueLabel(QString::number(changedValue));
    }

    this->update();
}

#endif
