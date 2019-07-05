//
// Created by Glenn R. Martin on 2019-06-21.
//

#include "../../Testing.hpp"
#include "../../../dice/transformers/bases/Xformer.h"

#include "../../../dice/transformers/ImageOrigin.h"
#include "../../../dice/transformers/Colorer.h"
#include "../../../dice/transformers/Thresholder.h"
#include "../../../dice/transformers/Contouring.h"
#include "../../../dice/transformers/Edger.h"
#include "../../../dice/JpegFile.h"
#include "../../../dice/DiceProc.h"

#include <opencv2/imgproc.hpp>

#include <iostream>

using JpegFile = cvdice::JpegFile;

TEST_CASE("cvdice::transformers Basic Dice", "[transformers]") {

    SECTION("IMG_6178-Scale.jpg") {
        JpegFile* jpeg = JpegFile::fromFile("dice/IMG_6178-Scale.jpg");

        REQUIRE(jpeg->expectedPips.size() > 0);

        auto result = cvdice::DiceProc::getBasicDicePips(jpeg, {
            STRUKEY(colorerValue) 1,
            STRUKEY(thresholderType) cv::ThresholdTypes::THRESH_TOZERO,
            STRUKEY(thresholderValue) 218,
            STRUKEY(contourMode) cv::RetrievalModes::RETR_CCOMP,
            STRUKEY(contourApproximation) 2,
            STRUKEY(epsilonDeviationDetectionPoly) 0.04
        });

        CAPTURE(result, jpeg->expectedPips);
        REQUIRE(result == jpeg->expectedPips);
    }

    SECTION("IMG_6179-Scale.jpg") {
        JpegFile* jpeg = JpegFile::fromFile("dice/IMG_6179-Scale.jpg");


        REQUIRE(jpeg->expectedPips.size() > 0);

        auto result = cvdice::DiceProc::getBasicDicePips(jpeg, {
            STRUKEY(colorerValue) 1,
            STRUKEY(thresholderType) cv::ThresholdTypes::THRESH_TOZERO,
            STRUKEY(thresholderValue) 218,
            STRUKEY(contourMode) cv::RetrievalModes::RETR_CCOMP,
            STRUKEY(contourApproximation) 2,
            STRUKEY(epsilonDeviationDetectionPoly) 0.04
        });

        CAPTURE(result, jpeg->expectedPips);
        REQUIRE(result == jpeg->expectedPips);
    }

//    SECTION("IMG_6181-Scale.jpg") {
//        JpegFile* jpeg = JpegFile::fromFile("dice/IMG_6181-Scale.jpg");
//
//        REQUIRE(jpeg->expectedPips.size() > 0);
//
//        auto result = cvdice::utils::DiceProc::getBasicDicePips(jpeg, {
//            STRUKEY(colorerValue) 1,
//            STRUKEY(thresholderType) cv::ThresholdTypes::THRESH_TOZERO,
//            STRUKEY(thresholderValue) 218,
//            STRUKEY(contourMode) cv::RetrievalModes::RETR_CCOMP,
//            STRUKEY(contourApproximation) 2,
//            STRUKEY(epsilonDeviationDetectionPoly) 0.04
//        });
//
//        CAPTURE(result, jpeg->expectedPips);
//        REQUIRE(result == jpeg->expectedPips);
//    }
}
