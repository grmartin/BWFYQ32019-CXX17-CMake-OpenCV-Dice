//
// Created by Glenn R. Martin on 2019-05-10.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"

#ifndef CVDICE_CVQTWIDGET_H
#define CVDICE_CVQTWIDGET_H

#include <opencv2/opencv.hpp>

#include <QWidget>
#include <QImage>
#include <QPainter>

using namespace cv;

namespace cvdice::ui::widgets {
#   define BYTES_PER 3

    class CVQTWidget : public QWidget {
    Q_OBJECT
    private:
        QImage _img;
        Mat _mat;

    protected:
        void paintEvent(QPaintEvent * /*event*/) override {
            QPainter painter(this);
            painter.drawImage(QPoint(0, 0), _img);
            painter.end();
        }

    public:
        explicit CVQTWidget(QWidget *parent = nullptr) : QWidget(parent) {}
        QSize sizeHint() const final { return _img.size(); }
        QSize minimumSizeHint() const final { return sizeHint(); }

    public slots:
        void paintMatrix(const Mat &image) {
            switch (image.type()) {
                case CV_8UC1: cvtColor(image, _mat, COLOR_GRAY2RGB); break;
                case CV_8UC3: cvtColor(image, _mat, COLOR_BGR2RGB); break;
            }

            if (!_mat.isContinuous()) _mat = _mat.clone();

            _img = QImage(_mat.data, _mat.cols, _mat.rows, _mat.cols * BYTES_PER, QImage::Format_RGB888);

            this->setFixedSize(image.cols, image.rows);

            repaint();
        }
    };
}
#undef BYTES_PER
#endif //CVDICE_CVQTWIDGET_H

#pragma clang diagnostic pop