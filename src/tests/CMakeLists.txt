if (CVD_TESTING)

    cmake_minimum_required(VERSION 3.13)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    project(CVDiceTests)

    add_executable(CVDiceTests
            main.cpp

            ResourceReader.cpp ResourceReader.h

            LibCVDiceAnnotation/Chunk.Test.cpp
            LibCVDiceAnnotation/JpegAnnotation.Test.cpp

            CVDice/utils/algorithm.Test.cpp CVDice/utils/hsv.Test.cpp

            CVDice/transformers/basicDiceSourceImages.Test.cpp)

    target_link_libraries(CVDiceTests PRIVATE CVDice)
    target_link_libraries(CVDiceTests PRIVATE LibCVDiceAnnotation)

    message(STATUS "Copying Testing Resources: ${TestResources}")
    add_custom_target(CVDiceTests_Resources)
    add_custom_command(TARGET CVDiceTests_Resources PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E
            copy_directory ${PROJECT_SOURCE_DIR}/res/ ${CMAKE_CURRENT_BINARY_DIR})
    add_dependencies(CVDiceTests CVDiceTests_Resources)

endif ()