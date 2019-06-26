#include <utility>

//
// Created by Glenn R. Martin on 2019-06-13.
//

#include "Terminus.h"

cvdice::transformers::Terminus::Terminus(std::function<void(cv::Mat)> fn) : Xformer(){
    this->completionFunction = fn;
}

void cvdice::transformers::Terminus::performUpdate() {
    display = source_image.clone();
    Xformer::update(display);
    this->completionFunction(display);
}

