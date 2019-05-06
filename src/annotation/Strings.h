//
// Created by Glenn R. Martin on 2019-05-05.
//

#ifndef CVDICE_STRINGS_H
#define CVDICE_STRINGS_H

#include <string>
#include <regex>

constexpr const char *trimmedChars = " \t\n\r";

inline std::string &rtrim(std::string &str, const char *tChars = trimmedChars) {
    str.erase(str.find_last_not_of(tChars) + 1);
    return str;
}

inline std::string &ltrim(std::string &str, const char *tChars = trimmedChars) {
    str.erase(0, str.find_first_not_of(tChars));
    return str;
}

inline std::string &trim(std::string &str, const char *tChars = trimmedChars) {
    return ltrim(rtrim(str, tChars), tChars);
}

inline std::vector<std::string> split(const std::string& s, const std::regex &regex) {
    return std::vector<std::string>(
            std::sregex_token_iterator(s.begin(), s.end(), regex, -1),
            std::sregex_token_iterator()
    );
}

#endif //CVDICE_STRINGS_H
