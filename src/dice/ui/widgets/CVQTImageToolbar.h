#ifndef CVQTIMAGETOOLBAR_H
#define CVQTIMAGETOOLBAR_H

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QWidget>
#endif

#include <functional>

#include "UiPredefine.h"

UI_PREDEFINE(CVQTImageToolbar);

class CVQTImageToolbarDelegate {
public:
    CVQTImageToolbarDelegate() = default;
    virtual void imageToolbarChanged(QWidget *sender, int value) = 0;
    virtual void imageToolbarEnabledChanged(QWidget *sender, bool isEnabled) = 0;
};

class CVQTImageToolbarDelegateWrapper : public CVQTImageToolbarDelegate{
protected:
    void imageToolbarChanged(QWidget *sender, int value) override;
    void imageToolbarEnabledChanged(QWidget *sender, bool isEnabled) override;

public:
    CVQTImageToolbarDelegateWrapper(std::function<void(QWidget *sender, int value)> fnImageToolbarChanged, std::function<void(QWidget *sender, bool isEnabled)> fnImageToolbarEnabledChanged) {
        onImageToolbarChanged = fnImageToolbarChanged;
        onImageToolbarEnabledChanged = fnImageToolbarEnabledChanged;
    }

public:
    std::function<void(QWidget *sender, int value)> onImageToolbarChanged;
    std::function<void(QWidget *sender, bool isEnabled)> onImageToolbarEnabledChanged;
};

class CVQTImageToolbar : public QWidget
{
    Q_OBJECT

protected:
    CVQTImageToolbarDelegate* _delegate;

public:

    explicit CVQTImageToolbar(const std::string& name, int curr, int min = 0, int max = 100, bool enabled = true);
    ~CVQTImageToolbar() override;

    QSize sizeHint() const override;

    QSize minimumSizeHint() const override;

    void setDelegate(CVQTImageToolbarDelegate* dele) {
        this->_delegate = dele;
    }

    void setValueLabel(const QString& string);

    void hideEnabled();

private slots:
    #pragma clang diagnostic push
    #pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

    void on_valueSlider_valueChanged(int value);
    void on_enabledCheckbox_stateChanged(int arg1);

    #pragma clang diagnostic pop

private:
    Ui::CVQTImageToolbar *ui;
};

#endif // CVQTIMAGETOOLBAR_H
