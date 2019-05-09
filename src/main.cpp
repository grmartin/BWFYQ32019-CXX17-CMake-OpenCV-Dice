#include <iostream>
#include "annotation/JpegAnnotation.h"
#include "dice/JpegFile.h"

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[], char* envp[]) {
    CommandLineParser parser( argc, argv, "{@input | ../data/fruits.jpg | input image}" );
    cvdice::JpegFile* file = cvdice::JpegFile::fromFile(fs::path(parser.get<String>("@input")));

    std::cout << "Got: " << *file << std::endl;
    return 0;
}