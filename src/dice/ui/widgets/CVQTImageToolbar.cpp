#include <iostream>
#include <dice/transformers/bases/Xformer.h>
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
    setValueLabel(QString::number(curr));
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

void CVQTImageToolbar::hideEnabled() {
    QSizePolicy szPol = ui->enabledCheckbox->sizePolicy();
    szPol.setRetainSizeWhenHidden(true);
    ui->enabledCheckbox->setSizePolicy(szPol);
    ui->enabledCheckbox->setHidden(true);
}

void CVQTImageToolbar::setValueLabel(const QString& string) {
    ui->valueLabel->setText(string);
}
