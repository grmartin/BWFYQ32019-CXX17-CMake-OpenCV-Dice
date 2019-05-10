//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_COLORER_H
#define CVDICE_COLORER_H

#import "XformerBase.h"

namespace cvdice::transformers {
    class Colorer : public XformerBase {
        int value = 0;

    public:
        explicit Colorer(const cv::Mat &sourceImage);

        void performUpdate() override;

    private:
        void buildUi() override;

    };
}

#endif //CVDICE_COLORER_H
