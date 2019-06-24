//
// Created by Glenn R. Martin on 2019-06-21.
//

#include "../../Testing.hpp"
#include "../../../dice/transformers/bases/XformerBase.h"

#include "../../../dice/transformers/ImageOrigin.h"
#include "../../../dice/transformers/Colorer.h"
#include "../../../dice/transformers/Thresholder.h"
#include "../../../dice/transformers/Contouring.h"
#include "../../../dice/transformers/Edger.h"
#include "../../../dice/JpegFile.h"

#include <opencv2/imgproc.hpp>

#include <iostream>

enum RoughShape {
    Square,
    Circle,
    Else
};

using Contours = cvdice::transformers::types::contours::Contours;
using Contour = cvdice::transformers::types::contours::Contour;

using namespace cvdice::transformers;
using namespace cvdice;

TEST_CASE("cvdice::transformers Basic Dice", "[transformers]") {

    SECTION("IMG_6178-Scale.jpg") {
        JpegFile* jpeg = JpegFile::fromFile("dice/IMG_6178-Scale.jpg");

        REQUIRE(jpeg->expectedPips.size() > 0);
        std::multiset<uint8_t> diceAndPipsSet;

        auto imageOrigin = new transformers::ImageOrigin(jpeg->matrix, false);
        auto colorer = new transformers::Colorer(1);
        auto thresholder = new transformers::Thresholder(3, 218);
        auto contouring = new transformers::Contouring(cv::RetrievalModes::RETR_CCOMP, 2);

        contouring->receivedDataListener = [jpeg, &diceAndPipsSet](transformers::types::contours::DataListenerEvent dataEvent) {
            int minimalDepth = MAX(-1, dataEvent.depth - 1); // this should filter us to only our subjects, the pips and dice faces.
            const auto epsilonDeviation = 0.04;


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
                                   cv::approxPolyDP(c.points, approxPts, perimeter * epsilonDeviation, true);

                                   auto points = approxPts.size();

                                   switch (points) {
                                       case 4: guess = RoughShape::Square;
                                       case 1: case 2: case 3: break;
                                       default: guess = RoughShape::Circle;
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
        };

        CHAIN_XFORMER(imageOrigin, colorer);
        CHAIN_XFORMER(colorer, thresholder);
        CHAIN_XFORMER(thresholder, contouring);

        imageOrigin->push();

        CAPTURE(diceAndPipsSet, jpeg->expectedPips);
        REQUIRE(diceAndPipsSet == jpeg->expectedPips);
    }

    SECTION("IMG_6179-Scale.jpg") {
        JpegFile* jpeg = JpegFile::fromFile("dice/IMG_6179-Scale.jpg");

        REQUIRE(jpeg->expectedPips.size() > 0);
        std::multiset<uint8_t> diceAndPipsSet;

        auto imageOrigin = new transformers::ImageOrigin(jpeg->matrix, false);
        auto colorer = new transformers::Colorer(1);
        auto thresholder = new transformers::Thresholder(3, 218);
        auto contouring = new transformers::Contouring(cv::RetrievalModes::RETR_CCOMP, 2);

        contouring->receivedDataListener = [jpeg, &diceAndPipsSet](transformers::types::contours::DataListenerEvent dataEvent) {
            int minimalDepth = MAX(-1, dataEvent.depth - 1); // this should filter us to only our subjects, the pips and dice faces.
            const auto epsilonDeviation = 0.04;


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
                                   cv::approxPolyDP(c.points, approxPts, perimeter * epsilonDeviation, true);

                                   auto points = approxPts.size();

                                   switch (points) {
                                       case 4: guess = RoughShape::Square;
                                       case 1: case 2: case 3: break;
                                       default: guess = RoughShape::Circle;
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
        };

        CHAIN_XFORMER(imageOrigin, colorer);
        CHAIN_XFORMER(colorer, thresholder);
        CHAIN_XFORMER(thresholder, contouring);

        imageOrigin->push();

        CAPTURE(diceAndPipsSet, jpeg->expectedPips);
        REQUIRE(diceAndPipsSet == jpeg->expectedPips);
    }

    SECTION("IMG_6181-Scale.jpg") {
        JpegFile* jpeg = JpegFile::fromFile("dice/IMG_6181-Scale.jpg");

        REQUIRE(jpeg->expectedPips.size() > 0);
        std::multiset<uint8_t> diceAndPipsSet;

        auto imageOrigin = new transformers::ImageOrigin(jpeg->matrix, false);
        auto colorer = new transformers::Colorer(1);
        auto thresholder = new transformers::Thresholder(3, 167);
        auto contouring = new transformers::Contouring(cv::RetrievalModes::RETR_CCOMP, 2);

        contouring->receivedDataListener = [jpeg, &diceAndPipsSet](transformers::types::contours::DataListenerEvent dataEvent) {
            int minimalDepth = MAX(-1, dataEvent.depth - 1); // this should filter us to only our subjects, the pips and dice faces.
            const auto epsilonDeviation = 0.04;


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
                                   cv::approxPolyDP(c.points, approxPts, perimeter * epsilonDeviation, true);

                                   auto points = approxPts.size();

                                   switch (points) {
                                       case 4: guess = RoughShape::Square;
                                       case 1: case 2: case 3: break;
                                       default: guess = RoughShape::Circle;
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
        };

        CHAIN_XFORMER(imageOrigin, colorer);
        CHAIN_XFORMER(colorer, thresholder);
        CHAIN_XFORMER(thresholder, contouring);

        imageOrigin->push();

        CAPTURE(diceAndPipsSet, jpeg->expectedPips);
        REQUIRE(diceAndPipsSet == jpeg->expectedPips);
    }
}
