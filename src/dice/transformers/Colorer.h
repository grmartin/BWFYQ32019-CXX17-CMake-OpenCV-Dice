//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_COLORER_H
#define CVDICE_COLORER_H

#import "bases/XformerBase.h"

namespace cvdice::transformers {
    class Colorer : public XformerBase {
        int value = 0;

    public:
        explicit Colorer(const cv::Mat &sourceImage, int value = 0);

        void performUpdate() override;

    private:
        void buildUi() override;

#ifdef CVD_USE_QT5
        void imageToolbarChanged(CVQTImageToolbar *toolbar, int value) override;
#endif
    };
}

#endif //CVDICE_COLORER_H
