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
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

    void on_valueSlider_valueChanged(int value);
    void on_enabledCheckbox_stateChanged(int arg1);

#pragma clang diagnostic pop

private:
    Ui::CVQTPicker *ui;
};

#endif // CVQTPICKER_H
