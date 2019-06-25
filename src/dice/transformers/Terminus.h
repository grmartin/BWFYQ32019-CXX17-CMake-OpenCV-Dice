//
// Created by Glenn R. Martin on 2019-06-13.
//

#ifndef CVDICE_TERMINUS_H
#define CVDICE_TERMINUS_H

#import "bases/Xformer.h"

namespace cvdice::transformers {
    class Terminus : public Xformer {
        std::function<void(cv::Mat)> completionFunction;

    public:
        Terminus(std::function<void(cv::Mat)> fn);

        void performUpdate() override;
    };
}


#endif //CVDICE_TERMINUS_H
