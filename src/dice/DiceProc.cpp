//
// Created by Glenn R. Martin on 2019-06-25.
//

#include "DiceProc.h"

#include "dice/transformers/bases/Xformer.h"

#include "dice/transformers/ImageOrigin.h"
#include "dice/transformers/Colorer.h"
#include "dice/transformers/Thresholder.h"
#include "dice/transformers/Contouring.h"
#include "dice/transformers/Edger.h"

#include <opencv2/imgproc.hpp>

using namespace cvdice;

using Contours = cvdice::transformers::types::contours::Contours;
using Contour = cvdice::transformers::types::contours::Contour;
using RoughShape = cvdice::classification::RoughShape;

std::multiset<uint8_t> cvdice::DiceProc::getBasicDicePips(cvdice::JpegFile *jpeg, struct BasicConfig config) {
    std::multiset<uint8_t> diceAndPipsSet;

    if (jpeg == nullptr) {
        return diceAndPipsSet;
    }

    auto imageOrigin = new transformers::ImageOrigin(jpeg->matrix, false);
    auto colorer = new transformers::Colorer(config.colorerValue);
    auto thresholder = new transformers::Thresholder(config.thresholderType, config.thresholderValue);
    auto contouring = new transformers::Contouring(config.contourMode, config.contourApproximation);

    contouring->receivedDataListener = [jpeg, &diceAndPipsSet, config](transformers::types::contours::DataListenerEvent dataEvent) {
        int minimalDepth = MAX(-1, dataEvent.depth - 1); // this should filter us to only our subjects, the pips and dice faces.


        {
            Contours possibleDiceAndPips;
            std::vector<std::pair<Contour, RoughShape>> roughShapes;
            std::vector<std::pair<Contour, RoughShape>> safeShapes;
            std::map<int, int> diceAndPipValues = {};

            std::copy_if(dataEvent.contours.begin(), dataEvent.contours.end(), std::back_inserter(possibleDiceAndPips),
                         [minimalDepth](Contour c) { return c.hierarchy.depth >= minimalDepth; });

            std::transform(possibleDiceAndPips.begin(), possibleDiceAndPips.end(), std::back_inserter(roughShapes),
                           [&](Contour c) {
                               auto guess = RoughShape::Else;
                               std::vector<cv::Point> approxPts;
                               auto perimeter = cv::arcLength(c.points, true);
                               cv::approxPolyDP(c.points, approxPts, perimeter * config.epsilonDeviationDetectionPoly, true);

                               auto points = approxPts.size();

                               switch (points) {
                                   case 4: guess = RoughShape::Square;
                                   case 1: case 2: case 3: break;
                                   default: guess = RoughShape::Circle;
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

            return nullptr;
        }
    };

    CHAIN_XFORMER(imageOrigin, colorer);
    CHAIN_XFORMER(colorer, thresholder);
    CHAIN_XFORMER(thresholder, contouring);

    imageOrigin->push();

    return diceAndPipsSet;
}
