//
// Created by Glenn R. Martin on 2019-05-10.
//

#include "QT5Main.h"
#include "MainWindow.h"

#include <QApplication>
#include <opencv2/imgproc.hpp>

#include "../JpegFile.h"
#include "../DiceProc.h"
#include "../transformers/bases/Xformer.h"
#include "../transformers/ImageOrigin.h"
#include "../transformers/Colorer.h"
#include "../transformers/Thresholder.h"
#include "../transformers/AdaptiveThresholder.h"
#include "../transformers/Contouring.h"
#include "../transformers/Edger.h"
#include "../transformers/Terminus.h"

#include "widgets/CVQTImageToolbar.h"
#include "widgets/CVQTWidget.h"

namespace cvdice::ui {
    void imagePipelineTermination(MainWindow *mainWindow, transformers::Terminus *terminus, const cv::Mat& image);
}

using Contours = cvdice::transformers::types::contours::Contours;
using Contour = cvdice::transformers::types::contours::Contour;
using RoughShape = cvdice::classification::RoughShape;

void cvdice::ui::imagePipelineTermination(MainWindow* mainWindow, transformers::Terminus *terminus, const cv::Mat& image) {
    if (auto object = MainWindow::findByClassName(mainWindow, "cvdice::ui::widgets::CVQTWidget")) {
        dynamic_cast<ui::widgets::CVQTWidget *>(object)->paintMatrix(image);
    }
}

int cvdice::ui::QT5Main(int argc, char *argv[], char *envp[], cvdice::JpegFile *jpeg) {
    const auto blackColor = cv::Scalar(0,0,0);
    const auto whiteColor = cv::Scalar(255,255,255);

    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName("CVDice");
    MainWindow mainWindow(nullptr);

    auto mainWindowPtr = &mainWindow;

    mainWindow.show();

    // From this point forward, were a playground... code will change frequently to test algorithms.

    auto imageOrigin = NEW_XFORMER_AUTO(transformers::ImageOrigin, jpeg->matrix, false);
    auto colorer = NEW_XFORMER_AUTO(transformers::Colorer, 1);
//    auto thresholder = NEW_XFORMER_AUTO(transformers::AdaptiveThresholder, cv::THRESH_BINARY, cv::ADAPTIVE_THRESH_MEAN_C, 1, 11);
    auto thresholder = new transformers::Thresholder(3, 218);
    auto edger = NEW_XFORMER_AUTO(transformers::Edger);
    auto contouring = NEW_XFORMER_AUTO(transformers::Contouring, cv::RetrievalModes::RETR_CCOMP, 2);
    transformers::Terminus *terminus = NEW_XFORMER_AUTO(transformers::Terminus, [&](cv::Mat image) { imagePipelineTermination(mainWindowPtr, terminus, image); });

    auto bindAndDelegateE = [&](CVQTImageToolbar *toolbar, cvdice::transformers::Xformer* xformer, std::function<void(QWidget *sender, int value)> fn) {
        toolbar->setDelegate(new CVQTImageToolbarDelegateWrapper(
            [=](QWidget *sender, int value){
                try { fn(sender, value); } catch (Exception& ignored) {}
                toolbar->setValueLabel(QString::number(value));
            },
            [=](QWidget *sender, bool enabled){ xformer->enabled = enabled; xformer->update(); }
        ));

        QString name = toolbar->objectName();
        return mainWindow.addToolbar(toolbar, &name);
    };

    auto bindAndDelegateD = [&](CVQTImageToolbar *toolbar, cvdice::transformers::Xformer* xformer, std::function<void(QWidget *sender, int value)> fn) {
        toolbar->hideEnabled();
        bindAndDelegateE(toolbar, xformer, fn);
    };

    // Colorer
    bindAndDelegateE(new CVQTImageToolbar("Color Value:", colorer->getValue(), 0, colorer->validValues.size() - 1, colorer->enabled), colorer, [&](QWidget *sender, int value){ colorer->setValue(value); });

    // Thresholder
    bindAndDelegateE(new CVQTImageToolbar("Thresh Type:", thresholder->getType(), 0, thresholder->getMaxType(), thresholder->enabled), thresholder,  [&](QWidget *sender, int value){ thresholder->setType(value); });
    bindAndDelegateD(new CVQTImageToolbar("Thresh Value:", thresholder->getValue(), 0, thresholder->getMaxValue(), thresholder->enabled), thresholder, [&](QWidget *sender, int value){ thresholder->setValue(value); });

    // Edger
    bindAndDelegateE(new CVQTImageToolbar("Canny Kern:", edger->getKernelSize(), 0, edger->getMaxKernelSize(), edger->enabled), edger,  [&](QWidget *sender, int value){ edger->setKernelSize(value); });
    bindAndDelegateD(new CVQTImageToolbar("Canny Thresh Value:", edger->getThresholdValue(), 0, edger->getMaxThreshold(), edger->enabled), edger, [&](QWidget *sender, int value){ edger->setThresholdValue(value); });
    bindAndDelegateD(new CVQTImageToolbar("Canny Ratio:", edger->getRatio(), 0, edger->getMaxRatio(), edger->enabled), edger, [&](QWidget *sender, int value){ edger->setRatio(value); });


    // Contouring
    bindAndDelegateE(new CVQTImageToolbar("Retrieval Mode:", contouring->getRetr(), 0, contouring->getMaxRetr(), contouring->enabled), contouring,  [&](QWidget *sender, int value){ contouring->setRetr(value); });
    bindAndDelegateD(new CVQTImageToolbar("Approx Type:", contouring->getApprox(), 0, contouring->getMaxApprox(), contouring->enabled), contouring, [&](QWidget *sender, int value){ contouring->setApprox(value); });

    edger->enabled = false;

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
                                   case RoughShape::Square: poorMansShadow("S", c.center); break;
                                   case RoughShape::Circle: poorMansShadow("C", c.center); break;
                                   default: /* No-Op */;
                               }

                               return std::make_pair(c, guess);
                           });

            std::copy_if(roughShapes.begin(), roughShapes.end(), std::back_inserter(safeShapes),
                         [](std::pair<Contour, RoughShape> pair) { return pair.second != RoughShape::Else; });

            std::sort(safeShapes.begin(), safeShapes.end(), [](auto a, auto b){
                return a.second < b.second;
            });

            std::for_each(safeShapes.begin(), safeShapes.end(), [&diceAndPipValues](auto pair){
                switch (pair.second) {
                    case RoughShape::Square: diceAndPipValues[pair.first.index] = 0; break;
                    case RoughShape::Circle: diceAndPipValues.at(pair.first.hierarchy.parent) = diceAndPipValues.at(pair.first.hierarchy.parent)+1; break;
                    default: /* No-Op */;
                }
            });

            std::for_each(diceAndPipValues.begin(), diceAndPipValues.end(), [&diceAndPipsSet](auto pair) {
                diceAndPipsSet.insert(static_cast<uint8_t>(pair.second));
            });
        }

        printf("EQUAL PIPS? %s", diceAndPipsSet == jpeg->expectedPips ? "TRUE" : "FALSE");

        return std::any(diceAndPipsSet);
    };

    CHAIN_XFORMER(imageOrigin, colorer);
    CHAIN_XFORMER(colorer, thresholder);
    CHAIN_XFORMER(thresholder, edger);
    CHAIN_XFORMER(edger, contouring);
    CHAIN_XFORMER(contouring, terminus);

    imageOrigin->push();
    return QApplication::exec();
}