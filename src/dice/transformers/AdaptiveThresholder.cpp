//
// Created by Glenn R. Martin on 2019-05-09.
//

#include "AdaptiveThresholder.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <utility>

#include "Colorer.h"
#include "../JpegFile.h"
#include "../../annotation/JpegAnnotation.h"


void cvdice::transformers::AdaptiveThresholder::performUpdate() {
    std::cout << "AThresh Type: " << type << ", Method: " << method << ", BS: " << ((blockSize+1)*2)+1 << ", C: " << c << std::endl;

    adaptiveThreshold(source_image.clone(), display, max_binary_value, type, method, ((blockSize+1)*2)+1, c);
    Xformer::update(display);
}
