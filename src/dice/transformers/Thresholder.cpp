//
// Created by Glenn R. Martin on 2019-05-09.
//

#include "Thresholder.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <utility>

#include "Colorer.h"
#include "../JpegFile.h"
#include "../../annotation/JpegAnnotation.h"

void cvdice::transformers::Thresholder::performUpdate() {
    std::cout << "Thresh Type: " << type << ", Value: " << value << std::endl;

    threshold(source_image.clone(), display, value, max_binary_value, type);
    Xformer::update(display);
}
