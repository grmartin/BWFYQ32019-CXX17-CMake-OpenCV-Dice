//
// Created by Glenn R. Martin on 2019-06-25.
//

#ifndef CVDICE_IDENTIFIABLE_H
#define CVDICE_IDENTIFIABLE_H


#include <string>
#include <map>
#include <any>

#define NEW_XFORMER(x, y, ...) ([&](){ auto tmp = new x(__VA_ARGS__); tmp->setIdentifierKey(y); return tmp; })()
#define NEW_XFORMER_AUTO(x, ...) ([&](){ auto tmp = new x(__VA_ARGS__); tmp->setIdentifierKey(#x); return tmp; })()

namespace cvdice::transformers {
    class Identifiable {
    private:
        std::string identifierKey{""};

    public:
        std::map<std::string, std::any> arbitraryValues;

    public:
        Identifiable();
        void setIdentifierKey(const std::string &identifierKey);
        const std::string &getIdentifierKey() const;
    };

}

#endif //CVDICE_IDENTIFIABLE_H
