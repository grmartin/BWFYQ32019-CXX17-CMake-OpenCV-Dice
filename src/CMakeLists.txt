cmake_minimum_required(VERSION 3.13)

message(STATUS "Initializing Hunter.")
include("cmake/ThirdParty/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.165.tar.gz"
        SHA1 "5a73f91df5f6109c0bb1104d0c0ee423f7bece79"
)

project(CVDice
        VERSION 0.0.0.0
        DESCRIPTION "A basic benchwork/play project to detect/ccount the pips on rolled dice using OpenCV"
        HOMEPAGE_URL "https://github.com/grmartin/BWFYQ32019-CXX17-CMake-OpenCV-Dice"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CVDICE_CMAKE_FIND_PATHS ./ ./lib/* ../stock/*)

#include("cmake/DebugBuildEnv.cmake")
include("cmake/OSDetection.cmake")

function(message_var msg varName)
    if (DEFINED ${varName})
        message(STATUS "${msg}: ${${varName}}")
    else ()
        message(STATUS "${msg}: <DEFAULT>")
    endif ()
endfunction()

if (CMAKE_BUILD_TYPE STREQUAL Testing OR CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CVD_TESTING true)
endif ()

# MSVC 2019 has std::filesystem, Apple as of Mojave does not so we must include Boost::filesystem, GCC also has it in a
# differnet place and support is shaky in 7 so lets go boost there too.

if (CVD_MSWIN)
    set(CVDICE_CMAKE_FIND_PATHS ../stock/OpenCV/Win64/opencv/build/x64/vc15/lib ${CVDICE_FIND_PATHS})
    include_directories(SYSTEM ../stock/OpenCV/Win64/opencv/sources/3rdparty)
elseif (CVD_MACOS)
    set(CVD_USE_BOOST_FS true)
    set(CVD_USE_QT5 true)
elseif (CVD_LINUX)
    set(CVD_USE_BOOST_FS true)
    set(CVD_USE_QT5 true)
endif ()

message_var("CMake Version" CMAKE_VERSION)
message_var("CMake Include Path" CMAKE_MODULE_PATH)
message_var("C++ Compiler" CMAKE_CXX_COMPILER_ID)
message_var("System Name" CMAKE_SYSTEM_NAME)

#include("cmake/DebugBuildEnv.cmake")

message(STATUS "")

# MANDATORY COMPONENTS -------------------------------------------------------------------------------------------------
# TODO: See if we can conditionally rebuild OpenCV only if its not found locally rather than assuming it is to be
#   via hunter... like we do QT5.
hunter_add_package(OpenCV COMPONENTS)
find_package(OpenCV CONFIG REQUIRED)


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

# OPTIONAL COMPONENTS --------------------------------------------------------------------------------------------------

if ("${CVD_USE_BOOST_FS}")
    hunter_add_package(Boost COMPONENTS filesystem)
    find_package(Boost CONFIG REQUIRED filesystem)
    message(STATUS "Using boost::filesystem")
else ()
    message(STATUS "Using std::filesystem")
endif ()

if ("${CVD_USE_QT5}") # https://doc.qt.io/qt-5/cmake-manual.html
    message(STATUS "QT5 library status:")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    # if you want to bypass hunter please see:
    #   https://github.com/Cockatrice/Cockatrice/issues/205#issuecomment-48788033
    find_package(Qt5 CONFIG REQUIRED Widgets Concurrent Core Gui OpenGL Test)

    if ("${Qt5Widgets_FOUND}")
        message(STATUS "    System Installation Found.")
    else ()
        message(STATUS "    Invoking Hunter.")
        hunter_add_package(Qt COMPONENTS qtbase)
    endif ()

    message(STATUS "    QT5::Core Version: ${Qt5Core_VERSION}")
    message(STATUS "    QT5::Gui Version: ${Qt5Gui_VERSION}")
    message(STATUS "    QT5::OpenGL Version: ${Qt5OpenGL_VERSION}")

    set(CVD_USE_QT5_VER_FOOTER_MSG "    (Ideally the above should match)")

    if (CVD_MACOS)
        # Have to link it manually because of cyclic dependencies in Qt
        find_package(Qt5PrintSupport REQUIRED)
        message(STATUS "    QT5::PrintSupport Version: ${Qt5PrintSupport_VERSION} [macOS Only]")

        message(STATUS ${CVD_USE_QT5_VER_FOOTER_MSG})

        # Sometimes this is missing on macOS, this typically means an old OS or QT Version.
        if (NOT TARGET Qt5::Widgets)
            message(FATAL_ERROR "*** No Qt5::Widgets target ***")
        else ()
            message(STATUS "    Qt5::Widgets Target: Found [macOS Only]")
        endif ()

        # Modern QT requires Security.framework to detect/handle Sandboxing, so lets link to that too.
        find_library(SECURITY_FRAMEWORK Security)
    else ()
        message(STATUS ${CVD_USE_QT5_VER_FOOTER_MSG})
    endif ()
endif ()

# TARGET CONFIGURATION HELPERS -----------------------------------------------------------------------------------------

function(linkGUI target)
    if ("${CVD_USE_QT5}")

        target_link_libraries(${target} PUBLIC Qt5::Widgets)
        target_compile_definitions(${target} PUBLIC CVD_USE_QT5=1)
        target_include_directories(${target} SYSTEM PRIVATE ./dice/ui)

        set_property(TARGET ${target} APPEND PROPERTY AUTOMOC ON)
        set_property(TARGET ${target} APPEND PROPERTY AUTOUIC ON)

        if (CVD_MACOS)
            target_link_libraries(${target} PUBLIC ${SECURITY_FRAMEWORK})
            target_link_libraries(${target} PUBLIC Qt5::PrintSupport)
        endif ()
    endif ()
endfunction()

function(linkAll target)
    if ("${CVD_USE_BOOST_FS}")
        target_compile_definitions(${target} PUBLIC CVD_USE_BOOST_FS=1 BOOST_NO_AUTO_PTR)
        target_link_libraries(${target} PUBLIC Boost::filesystem)
    endif ()

    if (CVD_LINUX)
        target_compile_options(${target} PUBLIC -std=c++17)
    endif ()
endfunction()

# TARGETS + OUTPUTS ----------------------------------------------------------------------------------------------------

if ("${CVD_USE_QT5}")
    list(APPEND CVDice_Sources_QT5
            # UI
            dice/ui/QT5Main.cpp dice/ui/QT5Main.h

            dice/transformers/bases/QT5Xformer.h

            dice/ui/MainWindow.cpp dice/ui/MainWindow.h dice/ui/MainWindow.ui

            dice/ui/widgets/CVQTWidget.h
            dice/ui/widgets/CVQTImageToolbar.h dice/ui/widgets/CVQTImageToolbar.cpp dice/ui/widgets/CVQTImageToolbar.ui

            dice/ui/widgets/InvokeDelegate.h dice/ui/widgets/UiPredefine.h
            dice/transformers/bases/QT5Xformer.cpp)
endif ()

add_executable(CVDice

        main.cpp

        dice/JpegFile.cpp dice/JpegFile.h

        dice/transformers/bases/XformerBase.h dice/transformers/bases/Xformer.h dice/transformers/bases/Xformer.cpp

        dice/utils/algorithm.h

        dice/transformers/Thresholder.cpp dice/transformers/Thresholder.h
        dice/transformers/Colorer.cpp dice/transformers/Colorer.h
        dice/transformers/Edger.cpp dice/transformers/Edger.h
        dice/transformers/Contouring.cpp dice/transformers/Contouring.h

        ${CVDice_Sources_QT5}
       )

add_executable(CVDiceAnnotator annotation/main.cpp annotation/VecByte.h annotation/Chunk.h annotation/Strings.h)

add_library(LibCVDiceAnnotation
        annotation/JpegAnnotation.cpp annotation/JpegAnnotation.h
        )

if (CVD_TESTING)
    set_property(
            TARGET CVDice
            APPEND PROPERTY OUTPUT_NAME CVDice_Testable
    )
    set_property(
            TARGET CVDice
            APPEND PROPERTY ENABLE_EXPORTS 1
    )
endif ()

target_link_libraries(CVDice PRIVATE LibCVDiceAnnotation)
target_link_libraries(CVDiceAnnotator PRIVATE LibCVDiceAnnotation)
target_link_libraries(LibCVDiceAnnotation PUBLIC ${OpenCV_LIBS})

linkGUI(CVDice)
linkAll(CVDice)
linkAll(CVDiceAnnotator)
linkAll(LibCVDiceAnnotation)

add_subdirectory(tests)
