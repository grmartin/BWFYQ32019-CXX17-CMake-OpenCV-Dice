cmake_minimum_required(VERSION 3.13)

message(STATUS "Initializing Hunter.")
include("cmake/ThirdParty/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.23.198.tar.gz"
        SHA1 "f44b698691eedfe9d1ee6763a6fb9b4af7756c24"
)

project(CVDice
        VERSION 0.0.0.0
        DESCRIPTION "A basic benchwork/play project to detect/count the pips on rolled dice using OpenCV"
        HOMEPAGE_URL "https://github.com/grmartin/BWFYQ32019-CXX17-CMake-OpenCV-Dice")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CVDICE_SRC_ROOT ${PROJECT_SOURCE_DIR})

#include("cmake/DebugBuildEnv.cmake")
include("cmake/OSDetection.cmake")

function(message_var msg varName)
    if (DEFINED ${varName})
        message(STATUS "${msg}: ${${varName}}")
    else ()
        message(STATUS "${msg}: <DEFAULT>")
    endif ()
endfunction()

message_var("Hunter Cache Root" HUNTER_CACHED_ROOT)

if (CMAKE_BUILD_TYPE STREQUAL Testing)
    set(CVD_TESTING true)
endif ()

if (CVD_MSWIN)
    set(CVD_USE_BOOST_FS true)
    message(STATUS "Instructing MSVC++ to use C++17")
    add_compile_options(/std:c++17 /wd4068)

    if (CVD_MSWIN)
        # error LNK2038: mismatch detected for '_ITERATOR_DEBUG_LEVEL': value '2' doesn't match value '0' in main.cpp.obj
        add_compile_options(/DEBUG /Zi /MDd /D_ITERATOR_DEBUG_LEVEL=2)
    endif()

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
    message(STATUS "    QT5::Core Version: ${Qt5Core_VERSION}")
    message(STATUS "    QT5::Gui Version: ${Qt5Gui_VERSION}")
    message(STATUS "    QT5::OpenGL Version: ${Qt5OpenGL_VERSION}")

    set(CVD_USE_QT5_VER_FOOTER_MSG "    (Ideally the above should match)")

    if (CVD_MACOS)
        # Have to link it manually because of cyclic dependencies in Qt
        find_package(Qt5PrintSupport REQUIRED)
        message(STATUS "    QT5::PrintSupport Version: ${Qt5PrintSupport_VERSION} [macOS Only]")

        # Sometimes this is missing on macOS, this typically means an old OS or QT Version.
        if (NOT TARGET Qt5::Widgets)
            message(FATAL_ERROR "*** No Qt5::Widgets target ***")
        else ()
            message(STATUS "    Qt5::Widgets Target: Found [macOS Only]")
        endif ()

        message(STATUS ${CVD_USE_QT5_VER_FOOTER_MSG})

        # Modern QT requires Security.framework to detect/handle Sandboxing, so lets link to that too.
        find_library(SECURITY_FRAMEWORK Security)
    else ()
        message(STATUS ${CVD_USE_QT5_VER_FOOTER_MSG})
    endif ()
endif ()

# TARGET CONFIGURATION HELPERS -----------------------------------------------------------------------------------------

function(linkGUI target mocit)
    if ("${CVD_USE_QT5}")

        target_link_libraries(${target} PUBLIC Qt5::Widgets)
        target_compile_definitions(${target} PUBLIC CVD_USE_QT5=1)
        target_include_directories(${target} SYSTEM PUBLIC ${PROJECT_SOURCE_DIR}/dice/ui)

        if (${mocit})
            set_property(TARGET ${target} APPEND PROPERTY AUTOMOC ON)
            set_property(TARGET ${target} APPEND PROPERTY AUTOUIC ON)
        endif ()

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

add_executable(CVDice main.cpp)

add_library(CVDiceBase STATIC
        dice/JpegFile.cpp dice/JpegFile.h

        dice/transformers/bases/Xformer.h dice/transformers/bases/Xformer.cpp
        dice/transformers/bases/Identifiable.cpp dice/transformers/bases/Identifiable.h

        dice/utils/algorithm.h

        dice/transformers/Thresholder.cpp dice/transformers/Thresholder.h
        dice/transformers/AdaptiveThresholder.cpp dice/transformers/AdaptiveThresholder.h
        dice/transformers/Colorer.cpp dice/transformers/Colorer.h
        dice/transformers/Edger.cpp dice/transformers/Edger.h
        dice/transformers/Contouring.cpp dice/transformers/Contouring.h
        dice/transformers/Terminus.cpp dice/transformers/Terminus.h

        dice/utils/hsv.h

        dice/transformers/ImageOrigin.cpp dice/transformers/ImageOrigin.h
        dice/DiceProc.cpp dice/DiceProc.h)

if ("${CVD_USE_QT5}")
    add_library(CVDiceQT STATIC
            # UI
            dice/ui/QT5Main.cpp dice/ui/QT5Main.h

            dice/ui/MainWindow.cpp dice/ui/MainWindow.h dice/ui/MainWindow.ui

            dice/ui/widgets/CVQTWidget.h
            dice/ui/widgets/CVQTImageToolbar.h dice/ui/widgets/CVQTImageToolbar.cpp dice/ui/widgets/CVQTImageToolbar.ui
            dice/ui/widgets/CVQTPicker.h dice/ui/widgets/CVQTPicker.cpp dice/ui/widgets/CVQTPicker.ui

            dice/ui/widgets/InvokeDelegate.h dice/ui/widgets/UiPredefine.h
            dice/ui/MainWindowListColDelegate.h dice/ui/CVQTTag.h)
endif ()
#            dice/ui/ModalitySelectionWindow.cpp dice/ui/ModalitySelectionWindow.h dice/ui/ModalitySelectionWindow.ui

add_executable(CVDiceAnnotator
        annotation/main.cpp
        annotation/VecByte.h annotation/Chunk.h annotation/Strings.h
        annotation/MSSupport.h)

add_library(LibCVDiceAnnotation STATIC
        annotation/JpegAnnotation.cpp annotation/JpegAnnotation.h)

foreach(project CVDiceBase LibCVDiceAnnotation)
    message(STATUS "Project ${project} set to C++17")
    set_target_properties(${project}
        PROPERTIES
        # Enable C++17 standard compliance
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )
    if (CVD_MSWIN)
        set_property(TARGET ${project}
                APPEND
                PROPERTY CXX_FLAGS "/std:c++17")
    endif()
endforeach()

# TARGETS > LINKING ----------------------------------------------------------------------------------------------------

target_link_libraries(CVDice PRIVATE CVDiceBase)
target_link_libraries(CVDiceBase PUBLIC LibCVDiceAnnotation)
target_link_libraries(CVDiceAnnotator PRIVATE LibCVDiceAnnotation)
target_link_libraries(LibCVDiceAnnotation PUBLIC ${OpenCV_LIBS})

set_target_properties(LibCVDiceAnnotation PROPERTIES LIBRARY_OUTPUT_NAME "CVDiceAnnotation")

linkAll(CVDiceBase)
linkAll(CVDiceAnnotator)
linkAll(LibCVDiceAnnotation)

if ("${CVD_USE_QT5}")
    target_link_libraries(CVDiceQT PRIVATE CVDiceBase)

    target_link_libraries(CVDice PRIVATE CVDiceQT)

    linkGUI(CVDiceQT true)
    linkGUI(CVDiceBase false) # Switch Xformers to QT Versions.

    linkAll(CVDiceQT)
endif ()

add_subdirectory(tests)
