#include <iostream>
#include <dice/transformers/bases/XformerBase.h>
#include "CVQTImageToolbar.h"
#include "ui_CVQTImageToolbar.h"
#include "InvokeDelegate.h"

CVQTImageToolbar::CVQTImageToolbar(const std::string &name, int curr, int min, int max, bool enabled) :
    QWidget(nullptr), ui(new Ui::CVQTImageToolbar) {

    ui->setupUi(this);
    this->_delegate = nullptr;
    ui->valueSlider->setMaximum(max);
    ui->valueSlider->setMinimum(min);
    ui->valueSlider->setValue(curr);
    ui->enabledCheckbox->setTristate(false);
    ui->enabledCheckbox->setChecked(enabled ? Qt::Checked : Qt::Unchecked);
    ui->nameLabel->setText(QString::fromStdString(name));
    ui->valueLabel->setText("");
}

CVQTImageToolbar::~CVQTImageToolbar() {
    delete ui;
}

void CVQTImageToolbar::on_valueSlider_valueChanged(int value) {
    INVOKE_DELEGATE(this->_delegate, imageToolbarChanged, value);
}

void CVQTImageToolbar::on_enabledCheckbox_stateChanged(int arg1) {
    INVOKE_DELEGATE(this->_delegate, imageToolbarEnabledChanged, arg1 == Qt::Checked);
}

QSize CVQTImageToolbar::sizeHint() const {
    return ui->horizontalLayoutWidget->sizeHint();
}

QSize CVQTImageToolbar::minimumSizeHint() const {
    return ui->horizontalLayoutWidget->minimumSizeHint();
}
