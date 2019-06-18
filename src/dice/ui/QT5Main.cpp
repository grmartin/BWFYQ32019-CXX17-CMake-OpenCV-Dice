//
// Created by Glenn R. Martin on 2019-05-10.
//

#include "QT5Main.h"
#include "MainWindow.h"

#include <QApplication>
#include <dice/JpegFile.h>
#include <opencv2/imgproc.hpp>

#include "dice/transformers/bases/XformerBase.h"
#include "../transformers/Colorer.h"
#include "../transformers/Thresholder.h"
#include "../transformers/Contouring.h"
#include "../transformers/Edger.h"

enum RoughShape {
    Square,
    Circle,
    Else
};

using Contours = cvdice::transformers::types::contours::Contours;
using Contour = cvdice::transformers::types::contours::Contour;

int cvdice::ui::QT5Main(int argc, char *argv[], char *envp[], cvdice::JpegFile *jpeg) {
    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName("CVDice");
    MainWindow mainWindow(nullptr);

    auto mainWindowPtr = std::shared_ptr<QMainWindow>(&mainWindow);

    mainWindow.show();

    auto colorer = new transformers::Colorer(jpeg->matrix, 1);
    auto thresholder = new transformers::Thresholder(jpeg->matrix, 3, 218);
    auto edger = new transformers::Edger(jpeg->matrix);
    auto contouring = new transformers::Contouring(jpeg->matrix, cv::RetrievalModes::RETR_CCOMP, 2);

    auto uiAppendToolbarFn = [&mainWindow](CVQTImageToolbar *toolbar) {
        QString name = toolbar->objectName();
        return mainWindow.addToolbar(toolbar, &name);
    };

    edger->enabled = false;

    colorer->showFor(mainWindowPtr, uiAppendToolbarFn);
    thresholder->showFor(mainWindowPtr, uiAppendToolbarFn);
    edger->showFor(mainWindowPtr, uiAppendToolbarFn);
    contouring->showFor(mainWindowPtr, uiAppendToolbarFn);

    contouring->receivedDataListener = [](transformers::types::contours::DataListenerEvent x) {
        int minimalDepth = MAX(-1, x.depth - 1); // this should filter us to only our subjects, the pips and dice faces.

        Contours possibleDiceAndPips;
        std::vector<std::pair<Contour, RoughShape>> roughShapes;
        std::copy_if(x.contours.begin(), x.contours.end(), std::back_inserter(possibleDiceAndPips), [minimalDepth](Contour c){ return c.hierarchy.depth >= minimalDepth; } );

        auto nudge = [](cv::Point pt, int x, int y){
            return cv::Point(pt.x + x, pt.y + y);
        };

        auto poorMansShadow = [&](const cv::String& text, cv::Point org) {
            cv::putText(*x.sourceImage, text, nudge(org, 1, 1), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,0), 1);
            cv::putText(*x.sourceImage, text, nudge(org, -1, 1), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,0), 1);
            cv::putText(*x.sourceImage, text, nudge(org, 1, -1), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,0), 1);
            cv::putText(*x.sourceImage, text, nudge(org, -1, -1), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,0), 1);
            cv::putText(*x.sourceImage, text, org, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255,255,255), 1);
        };

        auto epsilonDeviation = 0.04;

        std::transform(possibleDiceAndPips.begin(), possibleDiceAndPips.end(), std::back_inserter(roughShapes), [&](Contour c){
            auto guess = RoughShape::Else;
            std::vector<cv::Point> approxPts;
            auto perimeter = cv::arcLength(c.points, true);
            cv::approxPolyDP(c.points, approxPts, perimeter*epsilonDeviation, true);

            auto points = approxPts.size();

            switch (points) {
                case 4: guess = RoughShape::Square;
                case 1: case 2: case 3: break;
                default: guess = RoughShape::Circle;
            }

            switch (guess) {
                case Square:
                    poorMansShadow("S", c.center);
                    break;
                case Circle:
                    poorMansShadow("C", c.center);
                    break;
                default: /* No-Op */;
            }

            return std::make_pair(c, guess);
        });


        // TODO: DETERMINE DICE FACES, AND CHILDREN
        // TODO: COUNT AND SUPPLY VALUES

        printf("debug point 1");
    };

    CHAIN_XFORMER(colorer, thresholder);
    CHAIN_XFORMER(thresholder, edger);
    CHAIN_XFORMER(edger, contouring);

    colorer->update();

    return QApplication::exec();
}