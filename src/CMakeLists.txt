cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CVDICE_CMAKE_FIND_PATHS ./ ./lib/* ../stock/*)

# MSVC 2019 has std::filesystem, Apple as of Mojave does not so we must include Boost::filesystem, GCC also has it in a
# differnet place and support is shaky in 7 so lets go boost there too.

if (UNIX AND ("${CMAKE_HOST_SYSTEM_NAME}" MATCHES "Linux"))
 set(LINUX true)
else()
 set(LINUX false)
endif()

if (WIN32 AND CMAKE_SYSTEM_VERSION)
 set(CVDICE_CMAKE_FIND_PATHS ../stock/OpenCV/Win64/opencv/build/x64/vc15/lib ${CVDICE_FIND_PATHS})
 include_directories(SYSTEM ../stock/OpenCV/Win64/opencv/sources/3rdparty)
elseif (APPLE)
 set(CVD_USE_BOOST_FS true)
 set(CVD_USE_HUNTER true)
elseif(LINUX)
 set(CVD_USE_BOOST_FS true)
 set(CVD_USE_HUNTER true)
endif()


if("${CVD_USE_HUNTER}")
 message(STATUS "Initializing Hunter.")
 include("cmake/HunterGate.cmake")
 HunterGate(
         URL "https://github.com/ruslo/hunter/archive/v0.23.165.tar.gz"
         SHA1 "5a73f91df5f6109c0bb1104d0c0ee423f7bece79"
 )
endif()

project(CVDice)

if("${CVD_USE_HUNTER}")
 if ("${CVD_USE_BOOST_FS}")
  hunter_add_package(Boost COMPONENTS filesystem)
  find_package(Boost CONFIG REQUIRED filesystem)
 endif()

 hunter_add_package(OpenCV COMPONENTS)
 find_package(OpenCV CONFIG REQUIRED)
endif()

message(STATUS "CMake Include Path: ${CMAKE_MODULE_PATH}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "System Name: ${CMAKE_SYSTEM_NAME}")

# include("cmake/DebugBuildEnv.cmake")

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED PATHS ${CVDICE_CMAKE_FIND_PATHS})

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(CVDice main.cpp)
add_executable(CVDiceAnnotator annotation/main.cpp annotation/VecByte.h annotation/Chunk.h annotation/Strings.h)

add_library(LibCVDiceAnnotation
        annotation/JpegAnnotation.cpp annotation/JpegAnnotation.h
)
set_target_properties(CVDice PROPERTIES
        ENABLE_EXPORTS 1
        OUTPUT_NAME CVDice_Testable
        # Test placing exe import library in unique directory.
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/exe
        )

target_link_libraries(CVDice LibCVDiceAnnotation)
target_link_libraries(CVDiceAnnotator LibCVDiceAnnotation)
target_link_libraries(LibCVDiceAnnotation PUBLIC ${OpenCV_LIBS})

if ("${CVD_USE_BOOST_FS}")
 message(STATUS "Using boost::filesystem")
 target_compile_definitions(LibCVDiceAnnotation PUBLIC CVD_USE_BOOST_FS=1 BOOST_NO_AUTO_PTR)
 target_link_libraries(LibCVDiceAnnotation PUBLIC Boost::filesystem)
else()
 message(STATUS "Using std::filesystem")
endif()

if (LINUX)
 target_compile_options(LibCVDiceAnnotation PUBLIC -std=c++17)
endif()

add_subdirectory(tests)