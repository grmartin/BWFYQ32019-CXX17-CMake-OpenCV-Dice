//
// Created by Glenn R. Martin on 2019-06-25.
//

#include "Identifiable.h"

cvdice::transformers::Identifiable::Identifiable() {
    this->arbitraryValues = {};
}

void cvdice::transformers::Identifiable::setIdentifierKey(const std::string &key) {
    if (this->identifierKey.length() == 0)
        this->identifierKey = key;
}

const std::string &cvdice::transformers::Identifiable::getIdentifierKey() const {
    return this->identifierKey;
}
