//
// Created by Glenn R. Martin on 4/30/2019.
//

#include <cstdlib>
#include <vector>
#include <iostream>
#include <locale>
#include <algorithm>
#include <regex>

#include "JpegAnnotation.h"
#include "Strings.h"

using namespace jpeganno;

int processArguments(std::vector<std::string> arguments);
void printHelp();
int getFromJpeg(std::vector<std::string> arguments);
int setInJpeg(std::vector<std::string> arguments);
int copyFromJpegToJpeg(std::vector<std::string> arguments);

typedef struct {
    std::string switchName;

    int (*action)(std::vector<std::string> arguments);
} callTable;

const std::vector<callTable> getCalls() {
    static const std::vector<callTable> calls = {
        {"get", getFromJpeg},
        {"set", setInJpeg},
        {"copy", copyFromJpegToJpeg}
    };

    return calls;
}

int main(int argc, char *argv[], char *envp[]) {
    if (argc >= 3) {
        std::vector<std::string> args;
        args.reserve(argc);

        for (int i = 1; i < argc; ++i) {
            args.emplace_back(argv[i]);
        }

        return processArguments(args);
    } else {
        printHelp();
        return EXIT_FAILURE;
    }
}

void printHelp() {
    std::cerr << "Execution: application <set|get> <jpeg_path> [<csv number values 1-6>]" << std::endl;
    std::cerr << "An exit code of 0 is successful, else error." << std::endl;
    std::cerr << "Values returned by get will be numeric CSV via stdout." << std::endl << std::endl;
}

int processArguments(std::vector<std::string> arguments) {
    const std::locale locale;
    auto switchValue = arguments.at(0);
    std::transform(switchValue.begin(), switchValue.end(), switchValue.begin(), ::tolower);
    switchValue = trim(switchValue);

    for (auto const &value: getCalls()) {
        if (switchValue == value.switchName) {
            std::vector<std::string> input(arguments.begin() + 1, arguments.end());
            try {
                return value.action(input);
            } catch (std::exception& e) {
				std::cerr << e.what() << std::endl;
                break;
            }
        }
    }

    printHelp();
    return EXIT_FAILURE;
}


int getFromJpeg(std::vector<std::string> arguments) {
	const auto switchValue = arguments.at(0);

    auto values = JpegAnnotation::parseExpectedValues(switchValue);

    if (values.empty()) {
        return EXIT_SUCCESS;
    }

    int i = 0;
    for (const uint8_t &piece : values) {
        i == 0 ? (std::cout << static_cast<unsigned>(piece)) : (std::cout << "," << static_cast<unsigned>(piece));
        i++;
    }

    return EXIT_SUCCESS;
}

int setInJpeg(std::vector<std::string> arguments) {
    const std::regex regex("[,;]");
    auto const fileName = arguments.at(0);
    auto const values = split(trim(arguments.at(1)), regex);

    std::vector<uint8_t> valueInts;
    valueInts.reserve(values.size());

    for (auto &value: values) {
        valueInts.push_back(std::stoi(value));
    }

    JpegAnnotation::writeExpectedValues(fileName, valueInts);

    return EXIT_SUCCESS;
}

int copyFromJpegToJpeg(std::vector<std::string> arguments) {
    auto const fileName1 = arguments.at(0);
    auto const fileName2 = arguments.at(1);

    auto values = JpegAnnotation::parseExpectedValues(fileName1);

    if (values.empty()) {
        return EXIT_SUCCESS;
    }

    JpegAnnotation::writeExpectedValues(fileName2, values);

    return EXIT_SUCCESS;
}

