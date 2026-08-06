#ifndef CVQTPICKER_H
#define CVQTPICKER_H


#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QWidget>
#endif

#include "UiPredefine.h"
#include "CVQTImageToolbar.h"

UI_PREDEFINE(CVQTPicker);

namespace Ui {
class CVQTPicker;
}

class CVQTPicker : public QWidget
{
    Q_OBJECT

public:
    explicit CVQTPicker(QWidget *parent = nullptr);
    ~CVQTPicker();

    QSize sizeHint() const override;

    QSize minimumSizeHint() const override;

    void setDelegate(CVQTImageToolbarDelegate* dele) {
        this->_delegate = dele;
    }

    void hideEnabled();

protected:
    CVQTImageToolbarDelegate* _delegate;

private slots:
// The pragmas are CLion-only (its inspector flags these auto-connected
// slots as unused); real compilers would warn "unknown pragma" under
// -Wall, so hide them from anything but CLion's parser.
#ifdef __CLION_IDE__
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#endif

    void on_valueSlider_valueChanged(int value);
    void on_enabledCheckbox_stateChanged(int arg1);

#ifdef __CLION_IDE__
#pragma clang diagnostic pop
#endif

private:
    Ui::CVQTPicker *ui;
};

#endif // CVQTPICKER_H
