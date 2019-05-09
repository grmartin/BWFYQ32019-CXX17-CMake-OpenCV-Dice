//
// Created by Glenn R. Martin on 2019-05-09.
//

#include "../../Testing.hpp"
#include "../../../dice/utils/algorithm.h"

using namespace cvdice::algorithm;

TEST_CASE("cvdice::algorithm::for_each_i", "[utils]") {
    SECTION("Empty Array") {
        std::vector<int> vect = {};
        for_each_i(vect.begin(), vect.end(), [](auto ignored_1, auto ignored_2){
            SHOULD_NOT_BE_CALLED();
        });
    }
    SECTION("2 Item Array") {
        std::vector<int> vect = {8, 19};
        for_each_i(vect.begin(), vect.end(), [](auto val, auto i){
            CAPTURE(val, i);
            switch (val) {
                case 8: REQUIRE(i == 0); break;
                case 19: REQUIRE(i == 1); break;
                default: SHOULD_NOT_DEFAULT(); break;
            }
        });
    }
    SECTION("1 Item Array") {
        std::vector<int> vect = {2005};
        for_each_i(vect.begin(), vect.end(), [](auto val, auto i){
            CAPTURE(val, i);
            switch (val) { // NOLINT(hicpp-multiway-paths-covered)
                case 2005: REQUIRE(i == 0); break;
                default: SHOULD_NOT_DEFAULT(); break;
            }
        });
    }
}

TEST_CASE("cvdice::algorithm::for_each_fl", "[utils]") {
    SECTION("Empty Array") {
        std::vector<int> vect = {};
        for_each_fl(vect.begin(), vect.end(), [](auto ignored_1, auto ignored_2){
            SHOULD_NOT_BE_CALLED();
        });
    }
    SECTION("1 Item Array") {
        std::vector<int> vect = {2005};
        for_each_fl(vect.begin(), vect.end(), [](auto val, auto fl){
            CAPTURE(val, fl);
            switch (val) { // NOLINT(hicpp-multiway-paths-covered)
                case 2005: REQUIRE(fl == loc::first); break;
                default: SHOULD_NOT_DEFAULT(); break;
            }
        });
    }
    SECTION("2 Item Array") {
        std::vector<int> vect = {8, 19};
        for_each_fl(vect.begin(), vect.end(), [](auto val, auto fl){
            CAPTURE(val, fl);
            switch (val) {
                case 8: REQUIRE(fl == loc::first); break;
                case 19: REQUIRE(fl == loc::last); break;
                default: SHOULD_NOT_DEFAULT(); break;
            }
        });
    }
    SECTION("3 Item Array") {
        std::vector<int> vect = {100, 50, 0};
        for_each_fl(vect.begin(), vect.end(), [](auto val, auto fl){
            CAPTURE(val, fl);
            switch (val) {
                case 100: REQUIRE(fl == loc::first); break;
                case 50: REQUIRE(fl == loc::mid); break;
                case 0: REQUIRE(fl == loc::last); break;
                default: SHOULD_NOT_DEFAULT(); break;
            }
        });
    }
    SECTION("4 Item Array") {
        std::vector<int> vect = {1000, 12, 96, 127};
        for_each_fl(vect.begin(), vect.end(), [](auto val, auto fl){
            CAPTURE(val, fl);
            switch (val) {
                case 1000: REQUIRE(fl == loc::first); break;
                case 12: REQUIRE(fl == loc::mid); break;
                case 96: REQUIRE(fl == loc::mid); break;
                case 127: REQUIRE(fl == loc::last); break;
                default: SHOULD_NOT_DEFAULT(); break;
            }
        });
    }
}