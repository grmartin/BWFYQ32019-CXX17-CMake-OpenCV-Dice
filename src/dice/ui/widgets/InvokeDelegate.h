//
// Created by Glenn R. Martin on 2019-05-13.
//

#ifndef CVDICE_INVOKEDELEGATE_H
#define CVDICE_INVOKEDELEGATE_H

//#define INVOKE_DELEGATE_SC(d, t, x, y...) \
//    if (auto delegate = d.lock())  \
//        delegate->x(static_cast<t *>(this), y);
//
//#define INVOKE_DELEGATE_RC(d, t, x, y...) \
//    if (auto delegate = d.lock())  \
//        delegate->x(reinterpret_cast<t *>(this), y);

#define INVOKE_DELEGATE(d, x, y...) \
    if (d != nullptr)  \
        d->x(this, y);

#endif //CVDICE_INVOKEDELEGATE_H
