//
// Created by Glenn R. Martin on 2019-05-10.
//

#ifndef CVDICE_CVQTWIDGET_H
#define CVDICE_CVQTWIDGET_H

#include <opencv2/opencv.hpp>

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <QScrollArea>
#include <QLabel>

using namespace cv;

namespace cvdice{ namespace ui{ namespace widgets {
    #   define BYTES_PER 3

class CVQTWidget : public QScrollArea {
    Q_OBJECT

    private:
        QImage _img;
        QLabel* _label;
        Mat _mat;

    protected:
        void paintEvent(QPaintEvent * event) override {
            QPainter painter(this);
            painter.drawImage(QPoint(0, 0), _img, event->rect(), Qt::AutoColor);
            painter.end();
        }

    public:
        explicit CVQTWidget(QWidget *parent = nullptr) :
            QScrollArea(parent),
            _label(new QLabel) {
            _label->setBackgroundRole(QPalette::Base);
            _label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            _label->setScaledContents(true);

            this->setBackgroundRole(QPalette::Dark);
            this->setWidget(_label);
        }

    public slots:
        void paintMatrix(const Mat &image) {
            switch (image.type()) {
                case CV_8UC1: cvtColor(image, _mat, COLOR_GRAY2RGB); break;
                case CV_8UC3: cvtColor(image, _mat, COLOR_BGR2RGB); break;
            }

            if (!_mat.isContinuous()) _mat = _mat.clone();

            _img = QImage(_mat.data, _mat.cols, _mat.rows, _mat.cols * BYTES_PER, QImage::Format_RGB888);

            _label->setPixmap(QPixmap::fromImage(_img));
            _label->adjustSize();

            repaint();
        }
    };
}}}
#undef BYTES_PER
#endif //CVDICE_CVQTWIDGET_H
