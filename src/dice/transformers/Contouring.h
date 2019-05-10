//
// Created by Glenn R. Martin on 2019-05-10.
//

#ifndef CVDICE_CONTOURING_H
#define CVDICE_CONTOURING_H

#include "XformerBase.h"

namespace cvdice::transformers {
    class Contouring : public XformerBase {
    public:
        explicit Contouring(const cv::Mat &sourceImage) : XformerBase(sourceImage) {}

        void performUpdate() override;

    protected:
        void buildUi() override;
    };
};

#endif //CVDICE_CONTOURING_H
