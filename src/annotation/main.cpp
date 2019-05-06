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
int internalTest(std::vector<std::string> arguments);


typedef struct {
    std::string switchName;

    int (*action)(std::vector<std::string> arguments);
} callTable;

const std::vector<callTable> getCalls() {
    static const std::vector<callTable> calls = {
        {"get", getFromJpeg},
        {"set", setInJpeg},
        {"^internal_test", internalTest}
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

void loopErr(std::vector<uint8_t> values) {
    if (values.empty()) {
        std::cerr << "<EMPTY>" << std::endl;
        return;
    }

    int i = 0;
    for (const uint8_t &piece : values) {
        i == 0 ? (std::cerr << static_cast<unsigned>(piece)) : (std::cerr << "," << static_cast<unsigned>(piece));
        i++;
    }

    std::cerr << std::endl;
}


int internalTest1(std::vector<std::string> arguments) {
    const std::regex regex("[,;]");
    auto const fileName = arguments.at(0);
    auto const values = split(trim(arguments.at(1)), regex);

    std::vector<uint8_t> valueInts;
    valueInts.reserve(values.size());

    for (auto &value: values) {
        valueInts.push_back(std::stoi(value));
    }

    JpegAnnotation::writeExpectedValues(fileName, valueInts);
    std::vector<uint8_t> readValues = JpegAnnotation::parseExpectedValues(fileName);

    if (readValues == valueInts) {
        std::cout << "SUCCESS!" << std::endl;
        return EXIT_SUCCESS;
    } else {
        std::cerr << "FAILURE:" << std::endl;
        std::cerr << "\tIN:  ";

        loopErr(valueInts);
        std::cerr << "\tOUT: ";

        loopErr(readValues);

        return EXIT_FAILURE;
    }
}


int internalTest(std::vector<std::string> arguments) {
    auto run = internalTest1(arguments);

    if (run != EXIT_SUCCESS) return run;

    arguments[1] = "6,5,4,3,2,1,1,2";
    run = internalTest1(arguments);
    if (run != EXIT_SUCCESS) return run;
    arguments[1] = "1";
    run = internalTest1(arguments);
    if (run != EXIT_SUCCESS) return run;
    arguments[1] = "1,5,6,6,6,5,3,6,6,6,6,6,6,6,6,6,6,6,1,5,6,6,6,5,3,6,6,6,6,6,6,6,6,6,6,6";
    run = internalTest1(arguments);
    if (run != EXIT_SUCCESS) return run;
    return run;
}
