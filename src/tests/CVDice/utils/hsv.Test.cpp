//
// Created by Glenn R. Martin on 2019-06-13.
//

#include "../../Testing.hpp"
#include "../../../dice/utils/hsv.h"

using namespace cvdice::hsv;

TEST_CASE("cvdice::hsv::hsvToRgb", "[utils]") {
    SECTION("All 0's") {
        auto rgb = hsvToRgb(0,0,0);
        REQUIRE((int)rgb.r == 0);
        REQUIRE((int)rgb.g == 0);
        REQUIRE((int)rgb.b == 0);
    }
    SECTION("1, 100, 100 = 255, 4, 0") {
        auto rgb = hsvToRgb(1,100,100);
        REQUIRE((int)rgb.r == 255);
        REQUIRE((int)rgb.g == 4);
        REQUIRE((int)rgb.b == 0);
    }
    SECTION("175, 100, 100 = 0, 255, 234") {
        auto rgb = hsvToRgb(175,100,100);
        REQUIRE((int)rgb.r == 0);
        REQUIRE((int)rgb.g == 255);
        REQUIRE((int)rgb.b == 234);
    }
    SECTION("100, 100, 100 = 85, 255, 0") {
        auto rgb = hsvToRgb(100,100,100);
        REQUIRE((int)rgb.r == 85);
        REQUIRE((int)rgb.g == 255);
        REQUIRE((int)rgb.b == 0);
    }


    SECTION("175, 50, 100 = 128, 255, 244") {
        auto rgb = hsvToRgb(175,50,100);
        REQUIRE((int)rgb.r == 128);
        REQUIRE((int)rgb.g == 255);
        REQUIRE((int)rgb.b == 244);
    }
}