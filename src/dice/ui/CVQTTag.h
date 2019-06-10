//
// Created by Glenn R. Martin on 2019-06-10.
//

#ifndef CVDICE_CVQTTAG_H
#define CVDICE_CVQTTAG_H

constexpr const char* name = "CVDice:contextualName";

inline void setInternalContextName(QObject *object, QString context) {
    object->setProperty(name, context);
}

inline QString getInternalContextName(QObject *object) {
    return object->property(name).template value<QString>();
}

#endif //CVDICE_CVQTTAG_H
