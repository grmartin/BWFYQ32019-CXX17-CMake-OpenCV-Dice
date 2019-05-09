//
// Created by Glenn R. Martin on 2019-05-03.
//
#include "../catch.hpp"
#include "../../annotation/Chunk.h"

#ifndef CVDICE_CHUNK_TEST_H
#define CVDICE_CHUNK_TEST_H

using namespace jpeganno::util::chunk;

TEST_CASE("jpeganno::util::chunk", "[templates]") {
    GIVEN("an empty vector") {
        std::vector<int> x;
        WHEN("chunk size is 2 we expect an empty result vector") {
            auto out = chunk(x, 2);
            REQUIRE(out.empty());
        }

        WHEN("chunk size is 1 we expect an empty result vector") {
            auto out = chunk(x, 1);
            REQUIRE(out.empty());
        }

        WHEN("chunk size is 0 we expect an empty result vector") {
            auto out = chunk(x, 0);
            REQUIRE(out.empty());
        }
    }
    GIVEN("a 5 item integer vector.") {
        std::vector x = {1, 2, 3, 4, 5};
        WHEN("chunk size is 2 we expect 3 chunks with 2 of size 2 and then the remainder") {
            auto out = chunk(x, 2);
            REQUIRE(out.size() == 3);
            REQUIRE(out[0].size() == 2);
            REQUIRE(out[1].size() == 2);
            REQUIRE(out[2].size() == 1);
        }

        WHEN("chunk size is 1 we expect 5 chunks of size 1") {
            auto out = chunk(x, 1);
            REQUIRE(out.size() == 5);
            REQUIRE(out[0].size() == 1);
            REQUIRE(out[1].size() == 1);
            REQUIRE(out[2].size() == 1);
            REQUIRE(out[3].size() == 1);
            REQUIRE(out[4].size() == 1);
        }

        WHEN("chunk size is 0 we expect an empty result vector") {
            auto out = chunk(x, 0);
            REQUIRE(out.empty());
        }
    }
}
#endif //CVDICE_CHUNK_TEST_H
