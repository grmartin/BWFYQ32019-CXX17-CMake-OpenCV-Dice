#include <utility>


//
// Created by Glenn R. Martin on 2019-05-14.
//

#include "QT5Xformer.h"
#include "XformerBase.h"
#include <widgets/CVQTWidget.h>


QObject *cvdice::transformers::QT5Xformer::findByClassName(const QObject *const o, const char *name) {
    QObject *res = nullptr;
        foreach (QObject *c, o->children()) {
            if (res) break;

            if (QString::fromLocal8Bit(c->metaObject()->className()) == name) res = c;
            else res = findByClassName(c, name);
        }
    return res;
}

cvdice::transformers::QT5Xformer::QT5Xformer(const cv::Mat &sourceImage) : Xformer(sourceImage) {
    this->opaqueUiHandle = nullptr;
}

void
cvdice::transformers::QT5Xformer::showFor(const std::shared_ptr<QMainWindow> &appWindow, QT5UIAppender uiAppender) {
    this->window = appWindow;
    if (!this->has_built_ui) {
        this->appender = std::move(uiAppender);
        this->buildUi();
        this->appender = nullptr;
    }
}

void cvdice::transformers::QT5Xformer::updateWindow(const cv::Mat &mat) {
    if (auto actualWindow = this->window.lock().get()) {
        if (auto object = findByClassName(actualWindow, "cvdice::ui::widgets::CVQTWidget")) {
            dynamic_cast<ui::widgets::CVQTWidget *>(object)->paintMatrix(mat);
        };
    }
}

