//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_ADAPTIVETHRESHOLDER_H
#define CVDICE_ADAPTIVETHRESHOLDER_H

#include "bases/Xformer.h"
#include <set>
#include <opencv2/imgproc.hpp>

namespace cvdice::transformers {
    class AdaptiveThresholder : public Xformer {
        int type = cv::THRESH_BINARY;
        int method = cv::ADAPTIVE_THRESH_MEAN_C;
        int blockSize = 1; // This is a multiple, x = (y+1*2)+1;
        double c = 11;

        int const max_binary_value = 255;
        int const max_block_size = 126;

        const std::set<std::pair<const char*, int>> thresholdTypes = {
            {"THRESH_BINARY", cv::THRESH_BINARY},
            {"THRESH_BINARY_INV", cv::THRESH_BINARY_INV},
            {"THRESH_TRUNC", cv::THRESH_TRUNC},
            {"THRESH_TOZERO", cv::THRESH_TOZERO},
            {"THRESH_TOZERO_INV", cv::THRESH_TOZERO_INV}
        };

        const std::set<std::pair<const char*, int>> thresholdMethods = {
            {"ADAPTIVE_THRESH_MEAN_C", cv::ADAPTIVE_THRESH_MEAN_C},
            {"ADAPTIVE_THRESH_GAUSSIAN_C", cv::ADAPTIVE_THRESH_GAUSSIAN_C},
        };

    public:
        explicit AdaptiveThresholder(int type = cv::THRESH_BINARY, int method = cv::ADAPTIVE_THRESH_MEAN_C, int blockSize = 1, double c = 11) : Xformer() {
            this->method = method;
            this->type = type;
            this->blockSize = blockSize;
            this->c = c;
        }

        void performUpdate() override;

        void setType(int typeVal) {
            type = typeVal;
            this->update();
        }

        void setMethod(int methodVal) {
            method = methodVal;
            this->update();
        }

        void setBlockSize(int blockSizeVal) {
            blockSize = blockSizeVal;
            this->update();
        }

        void setC(double cVal) {
            c = cVal;
            this->update();
        }
    };
}
#endif //CVDICE_ADAPTIVETHRESHOLDER_H
