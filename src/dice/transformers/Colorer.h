//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_COLORER_H
#define CVDICE_COLORER_H

#include "bases/Xformer.h"

namespace cvdice::transformers {
    class Colorer : public Xformer {
        int value = 0;
    public:
        std::vector<int> validValues;

    public:
        explicit Colorer(int value = 0);

        void performUpdate() override;

        void setValue(int theValue) {
            value = theValue;
            this->update();
        }

        int getValue() const {
            return value;
        }
    };
}

#endif //CVDICE_COLORER_H
