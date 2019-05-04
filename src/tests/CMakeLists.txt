cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(CVDiceTests)

add_executable(CVDiceTests primary.cpp OnePXJpeg.hpp LibCVDiceAnnotation/Chunk.Test.h)
target_link_libraries(CVDiceTests CVDice)
target_link_libraries(CVDiceTests LibCVDiceAnnotation)