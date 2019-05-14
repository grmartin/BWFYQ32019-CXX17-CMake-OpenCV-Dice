#include <utility>
#include <iostream>

#include <opencv2/opencv.hpp>

#if CVD_USE_QT5
#   include "dice/ui/QT5Main.h"
#else
#   include "dice/transformers/bases/XformerBase.h"
#   include "dice/transformers/Colorer.h"
#   include "dice/transformers/Thresholder.h"
#   include "dice/transformers/Contouring.h"

using namespace cvdice::transformers;
#endif

#include "annotation/JpegAnnotation.h"
#include "dice/JpegFile.h"

using namespace cv;
constexpr std::string_view primaryWindowName = "Experimentation Window"; // NOLINT(cert-err58-cpp)

int main(int argc, char *argv[], char *envp[]) {
    std::string windowName = std::string{primaryWindowName};
    cvdice::JpegFile *file;
    Mat greyed;

    CommandLineParser parser(argc, argv, "{@input | ../data/fruits.jpg | input image}");
    file = cvdice::JpegFile::fromFile(fs::path(parser.get<String>("@input")));

    std::cout << "Got: " << *file << std::endl;

#if CVD_USE_QT5
    return cvdice::ui::QT5Main(argc, argv, envp, file);
#else
    cv::namedWindow(windowName, WINDOW_GUI_EXPANDED);

    auto colorer = new Colorer(file->matrix);
    auto thresholder = new Thresholder(file->matrix);
    auto contouring = new Contouring(file->matrix);

    colorer->showFor(windowName);
    thresholder->showFor(windowName);
    contouring->showFor(windowName);

    CHAIN_XFORMER(colorer, thresholder);
    CHAIN_XFORMER(thresholder, contouring);
    colorer->update();

    waitKey(0);
    return 0;
#endif
}