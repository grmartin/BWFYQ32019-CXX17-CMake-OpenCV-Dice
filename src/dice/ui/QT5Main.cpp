//
// Created by Glenn R. Martin on 2019-05-10.
//

#include "QT5Main.h"
#include "MainWindow.h"

#include <QApplication>
#include <dice/JpegFile.h>
#include <opencv2/imgproc.hpp>

#include "dice/transformers/bases/XformerBase.h"
#include "../transformers/ImageOrigin.h"
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
    const auto blackColor = cv::Scalar(0,0,0);
    const auto whiteColor = cv::Scalar(255,255,255);

    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName("CVDice");
    MainWindow mainWindow(nullptr);

    auto mainWindowPtr = std::shared_ptr<QMainWindow>(&mainWindow);

    mainWindow.show();

    auto imageOrigin = new transformers::ImageOrigin(jpeg->matrix, false);
    auto colorer = new transformers::Colorer(1);
    auto thresholder = new transformers::Thresholder(3, 218);
    auto edger = new transformers::Edger();
    auto contouring = new transformers::Contouring(cv::RetrievalModes::RETR_CCOMP, 2);

    auto uiAppendToolbarFn = [&mainWindow](CVQTImageToolbar *toolbar) {
        QString name = toolbar->objectName();
        return mainWindow.addToolbar(toolbar, &name);
    };

    edger->enabled = false;

    colorer->showFor(mainWindowPtr, uiAppendToolbarFn);
    thresholder->showFor(mainWindowPtr, uiAppendToolbarFn);
    edger->showFor(mainWindowPtr, uiAppendToolbarFn);
    contouring->showFor(mainWindowPtr, uiAppendToolbarFn);

    contouring->receivedDataListener = [blackColor, whiteColor, jpeg](transformers::types::contours::DataListenerEvent dataEvent) {
        int minimalDepth = MAX(-1, dataEvent.depth - 1); // this should filter us to only our subjects, the pips and dice faces.
        const auto epsilonDeviation = 0.04;

        std::multiset<uint8_t> diceAndPipsSet;

        {
            Contours possibleDiceAndPips;
            std::vector<std::pair<Contour, RoughShape>> roughShapes;
            std::vector<std::pair<Contour, RoughShape>> safeShapes;
            std::map<int, int> diceAndPipValues = {};

            std::copy_if(dataEvent.contours.begin(), dataEvent.contours.end(), std::back_inserter(possibleDiceAndPips),
                         [minimalDepth](Contour c) { return c.hierarchy.depth >= minimalDepth; });

            auto poorMansShadow = [&](const cv::String &text, cv::Point org) {
                cv::putText(*dataEvent.sourceImage, text, org, cv::FONT_HERSHEY_PLAIN, 1, blackColor, 4, cv::LINE_4);
                cv::putText(*dataEvent.sourceImage, text, org, cv::FONT_HERSHEY_PLAIN, 1, whiteColor, 1, cv::LINE_4);
            };

            std::transform(possibleDiceAndPips.begin(), possibleDiceAndPips.end(), std::back_inserter(roughShapes),
                           [&](Contour c) {
                               auto guess = RoughShape::Else;
                               std::vector<cv::Point> approxPts;
                               auto perimeter = cv::arcLength(c.points, true);
                               cv::approxPolyDP(c.points, approxPts, perimeter * epsilonDeviation, true);

                               auto points = approxPts.size();

                               switch (points) {
                                   case 4: guess = RoughShape::Square;
                                   case 1: case 2: case 3: break;
                                   default: guess = RoughShape::Circle;
                               }

                               switch (guess) {
                                   case Square: poorMansShadow("S", c.center); break;
                                   case Circle: poorMansShadow("C", c.center); break;
                                   default: /* No-Op */;
                               }

                               return std::make_pair(c, guess);
                           });

            std::copy_if(roughShapes.begin(), roughShapes.end(), std::back_inserter(safeShapes),
                         [](std::pair<Contour, RoughShape> pair) { return pair.second != Else; });

            std::sort(safeShapes.begin(), safeShapes.end(), [](auto a, auto b){
                return a.second < b.second;
            });

            std::for_each(safeShapes.begin(), safeShapes.end(), [&diceAndPipValues](auto pair){
                switch (pair.second) {
                    case Square: diceAndPipValues[pair.first.index] = 0; break;
                    case Circle: diceAndPipValues.at(pair.first.hierarchy.parent) = diceAndPipValues.at(pair.first.hierarchy.parent)+1; break;
                    default: /* No-Op */;
                }
            });

            std::for_each(diceAndPipValues.begin(), diceAndPipValues.end(), [&diceAndPipsSet](auto pair) {
                diceAndPipsSet.insert(static_cast<uint8_t>(pair.second));
            });
        }

        printf("EQUAL PIPS? %s", diceAndPipsSet == jpeg->expectedPips ? "TRUE" : "FALSE");
    };

    CHAIN_XFORMER(imageOrigin, colorer);
    CHAIN_XFORMER(colorer, thresholder);
    CHAIN_XFORMER(thresholder, edger);
    CHAIN_XFORMER(edger, contouring);

    imageOrigin->push();

    return QApplication::exec();
}