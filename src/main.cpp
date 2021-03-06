#include <utility>
#include <iostream>

#include <opencv2/opencv.hpp>

#if CVD_USE_QT5
#   include "dice/ui/QT5Main.h"
#endif

#include "annotation/JpegAnnotation.h"

#include "dice/JpegFile.h"

#include "dice/transformers/bases/Xformer.h"
#include "dice/transformers/ImageOrigin.h"
#include "dice/transformers/Colorer.h"
#include "dice/transformers/Thresholder.h"
#include "dice/transformers/Contouring.h"
#include "dice/transformers/Edger.h"
#include "dice/transformers/Terminus.h"

using namespace cvdice;
using namespace cv;

constexpr auto primaryWindowName = "Experimentation Window";

int main(int argc, char *argv[], char *envp[]) {
    std::string windowName = std::string{primaryWindowName};
    cvdice::JpegFile *file;
    Mat greyed;

    const String keys =
        "{help h usage ? |                    | print this message   }"
        "{@input         | <none>             | input image          }"
        #if CVD_USE_QT5
        "{noQT           |                    | Disable QT           }"
        #endif
        ;

    CommandLineParser parser(argc, argv, keys);
    parser.about("CVDice 1.0");

    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    file = cvdice::JpegFile::fromFile(fs::path(parser.get<String>("@input")));

    std::cout << "Got: " << *file << std::endl;

#if CVD_USE_QT5
    bool noQT = parser.has("noQT");

    if (!noQT) {
        return cvdice::ui::QT5Main(argc, argv, envp, file);
    }
#endif

    cv::namedWindow(windowName, WINDOW_GUI_EXPANDED);

    auto imageOrigin = new transformers::ImageOrigin(file->matrix, false);
    auto colorer = new transformers::Colorer(1);
    auto thresholder = new transformers::Thresholder(cv::ThresholdTypes::THRESH_TOZERO, 218);
    auto edger = new transformers::Edger();
    auto contouring = new transformers::Contouring(cv::RetrievalModes::RETR_CCOMP, 2);
    auto terminus = new transformers::Terminus([&windowName](cv::Mat image){
        imshow(windowName, image);
    });

    CHAIN_XFORMER(imageOrigin, colorer);
    CHAIN_XFORMER(colorer, thresholder);
    CHAIN_XFORMER(thresholder, edger);
    CHAIN_XFORMER(edger, contouring);
    CHAIN_XFORMER(contouring, terminus);

    imageOrigin->push();

    waitKey(0);
    return 0;
}