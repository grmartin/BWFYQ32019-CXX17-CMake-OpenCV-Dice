#ifndef TESTING_PRIMARY_INCLUDE_H
#define TESTING_PRIMARY_INCLUDE_H

#define FREE_SCOPE /* Hide this stuff from the developer / scoping is free. */
#define SETUP /* Setup */ FREE_SCOPE
#define TEARDOWN /* Teardown */ FREE_SCOPE
#define IIFE(lambda) (lambda)()

#include <regex>
#include <functional>
#include <sstream>

#include "catch.hpp"

#define SHOULD_NOT_BE_CALLED() FAIL("It is expected that we are never invoked.")
#define SHOULD_NOT_DEFAULT() FAIL("It is expected that this switch never defaults.")

#endif // TESTING_PRIMARY_INCLUDE_H