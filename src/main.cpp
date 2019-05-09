#include <utility>
#include <iostream>

#include <opencv2/opencv.hpp>

#include "annotation/JpegAnnotation.h"
#include "dice/JpegFile.h"

using namespace cv;

constexpr std::string_view primaryWindowName = "Experimentation Window"; // NOLINT(cert-err58-cpp)

class Colorer {
    int value = -1;

    Mat source_image;
    Mat display;

    std::string window_name;
    std::vector<int> validValues;

    bool has_built_ui = false;

public:
    std::function<void(Mat)> chainTo;

    explicit Colorer(const Mat &sourceImage) {

        this->source_image = sourceImage.clone();

        this->validValues = {
                COLOR_BGR2BGRA, COLOR_BGRA2BGR, COLOR_BGR2RGBA, COLOR_RGBA2BGR, COLOR_BGR2RGB, COLOR_BGRA2RGBA,
                COLOR_BGR2GRAY, COLOR_RGB2GRAY,
                COLOR_BGR2XYZ, COLOR_RGB2XYZ, COLOR_XYZ2BGR, COLOR_XYZ2RGB,
                COLOR_BGR2YCrCb, COLOR_RGB2YCrCb, COLOR_YCrCb2BGR, COLOR_YCrCb2RGB,
                COLOR_BGR2HSV, COLOR_RGB2HSV,
                COLOR_BGR2Lab, COLOR_RGB2Lab,
                COLOR_BGR2Luv, COLOR_RGB2Luv, COLOR_BGR2HLS, COLOR_RGB2HLS,
                COLOR_HSV2BGR, COLOR_HSV2RGB,
                COLOR_Lab2BGR, COLOR_Lab2RGB, COLOR_Luv2BGR, COLOR_Luv2RGB, COLOR_HLS2BGR, COLOR_HLS2RGB,
                COLOR_BGR2HSV_FULL, COLOR_RGB2HSV_FULL, COLOR_BGR2HLS_FULL, COLOR_RGB2HLS_FULL,
                COLOR_HSV2BGR_FULL, COLOR_HSV2RGB_FULL, COLOR_HLS2BGR_FULL, COLOR_HLS2RGB_FULL,
                COLOR_LBGR2Lab, COLOR_LRGB2Lab, COLOR_LBGR2Luv, COLOR_LRGB2Luv,
                COLOR_Lab2LBGR, COLOR_Lab2LRGB, COLOR_Luv2LBGR, COLOR_Luv2LRGB,
                COLOR_BGR2YUV, COLOR_RGB2YUV, COLOR_YUV2BGR, COLOR_YUV2RGB,
        };
    }

    void showFor(const std::string &windowName) {
        this->window_name = windowName;
    }

    void update() {

        auto selfUpdater = [](int pos, void *self) { reinterpret_cast<Colorer *>(self)->update(); };

        if (!has_built_ui) {
            has_built_ui = true;
            createTrackbar("Color Value: ",
                           window_name, &value,
                           this->validValues.size() - 1, selfUpdater, reinterpret_cast<void *>(this));
        }

        if (value >= 0) {
            std::cout << "Color Conversion: " << this->validValues[value] << std::endl;
            try {
                cv::cvtColor(source_image, display, this->validValues[value], 3);
            } catch (cv::Exception &ignored) { return; }
        }
        Mat show = value == -1 ? source_image : display;

        if (chainTo) {
            chainTo(show);
            return;
        }

        imshow(window_name, show);
    }
};

class Thresholder {
    int threshold_value = 0;
    int threshold_type = 3;

    int const max_value = 255;
    int const max_type = 4;
    int const max_binary_value = 255;

    Mat source_image;
    Mat display;

    std::string window_name;

    bool has_built_ui = false;

public:
    explicit Thresholder(const Mat &sourceImage) {
        this->source_image = sourceImage.clone();
    }

    void chainAction(const Mat &mat) {
        this->source_image = mat.clone();
        update();
    }

    void showFor(const std::string &windowName) {
        this->window_name = windowName;
    }

    void update() {

        std::cout << "Thresh Type: " << threshold_type << ", Value: " << threshold_value << std::endl;
        auto selfUpdater = [](int pos, void *self) { reinterpret_cast<Thresholder *>(self)->update(); };

        if (!has_built_ui) {
            has_built_ui = true;
            createTrackbar("Thresh Type:",
                           window_name, &threshold_type,
                           max_type, selfUpdater, reinterpret_cast<void *>(this));
            createTrackbar("Thresh Value: ",
                           window_name, &threshold_value,
                           max_value, selfUpdater, reinterpret_cast<void *>(this));
        }

        threshold(source_image, display, threshold_value, max_binary_value, threshold_type);
        imshow(window_name, display);
    }
};

#define CHAIN(first, second) first->chainTo = [&second](Mat mat) { second->chainAction(mat); }

int main(int argc, char *argv[], char *envp[]) {
    std::string windowName = std::string{primaryWindowName};
    cvdice::JpegFile *file;
    Mat greyed;

    CommandLineParser parser(argc, argv, "{@input | ../data/fruits.jpg | input image}");
    file = cvdice::JpegFile::fromFile(fs::path(parser.get<String>("@input")));

    std::cout << "Got: " << *file << std::endl;

    cv::namedWindow(windowName, WINDOW_AUTOSIZE);

    auto *colorer = new Colorer(file->matrix);
    auto *thresholder = new Thresholder(file->matrix);

    colorer->showFor(windowName);
    thresholder->showFor(windowName);

    CHAIN(colorer, thresholder);

    colorer->update();

    waitKey(0);
    return 0;
}