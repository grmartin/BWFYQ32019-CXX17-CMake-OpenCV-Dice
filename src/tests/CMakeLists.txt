if(CVD_TESTING)

 cmake_minimum_required(VERSION 3.13)

 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_CXX_STANDARD_REQUIRED ON)
 set(CMAKE_CXX_EXTENSIONS OFF)

 project(CVDiceTests)

 file(GLOB TestResources res/*)

 message(STATUS "Copying Testing Resources: ${TestResources}")

 add_executable(CVDiceTests
        main.cpp

        ResourceReader.cpp ResourceReader.h

        LibCVDiceAnnotation/Chunk.Test.cpp
        LibCVDiceAnnotation/JpegAnnotation.Test.cpp)

 add_custom_target(CVDiceTests_Resources)

 target_link_libraries(CVDiceTests CVDice)
 target_link_libraries(CVDiceTests LibCVDiceAnnotation)

 add_dependencies(CVDiceTests CVDiceTests_Resources)

 foreach(ResFile ${TestResources})
  add_custom_command(TARGET CVDiceTests_Resources PRE_BUILD
          COMMAND ${CMAKE_COMMAND} -E
          copy ${ResFile} ${CMAKE_CURRENT_BINARY_DIR} )
 endforeach()
endif()