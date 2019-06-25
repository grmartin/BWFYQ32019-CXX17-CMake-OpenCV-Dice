//
// Created by Glenn R. Martin on 2019-05-09.
//

#ifndef CVDICE_COLORER_H
#define CVDICE_COLORER_H

#import "bases/Xformer.h"

namespace cvdice::transformers {
    class Colorer : public Xformer {
        int value = 0;
        std::vector<int> validValues;

    public:
        explicit Colorer(int value = 0);

        void performUpdate() override;

        void setValue(int theValue) {
            value = theValue;
            this->update();
        }
    };
}

#endif //CVDICE_COLORER_H
