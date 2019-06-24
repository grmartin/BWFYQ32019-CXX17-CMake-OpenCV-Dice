//
// Created by Glenn R. Martin on 2019-05-14.
//

#include "Xformer.h"

#ifdef CVD_USE_QT5
#ifndef CVDICE_QT5XFORMER_H
#define CVDICE_QT5XFORMER_H

#include <widgets/CVQTImageToolbar.h>
#include <QMainWindow>
#include <QListWidgetItem>

namespace cvdice::transformers {
    class QT5Xformer;

    typedef std::function<QListWidgetItem *(CVQTImageToolbar *)> QT5UIAppender;

    class QT5Xformer : public Xformer, protected CVQTImageToolbarDelegate {
    protected:
        std::weak_ptr<QMainWindow> window;
        QT5UIAppender appender;
        void *opaqueUiHandle;

    public:
        explicit QT5Xformer();

        void showFor(const std::shared_ptr<QMainWindow> &window, QT5UIAppender uiAppender);

    private:
        void imageToolbarChanged(CVQTImageToolbar *toolbar, int value) override {
            // TODO: IMPLEMENT ON SUBCLASSES.
        }

        void imageToolbarEnabledChanged(CVQTImageToolbar *toolbar, bool isEnabled) override {
            this->enabled = isEnabled;
            this->update();
        }

    protected:
        void updateWindow(const cv::Mat &mat) override;

        QObject *findByClassName(const QObject *o, const char *name);
    };
}

#endif //CVDICE_QT5XFORMER_H
#endif