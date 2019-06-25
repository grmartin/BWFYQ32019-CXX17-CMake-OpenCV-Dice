#include "CVQTPicker.h"
#include "ui_CVQTPicker.h"
#include "InvokeDelegate.h"

CVQTPicker::CVQTPicker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CVQTPicker)
{
    ui->setupUi(this);
}

void CVQTPicker::on_valueSlider_valueChanged(int value) {
    INVOKE_DELEGATE(this->_delegate, imageToolbarChanged, value);
}

void CVQTPicker::on_enabledCheckbox_stateChanged(int arg1) {
    INVOKE_DELEGATE(this->_delegate, imageToolbarEnabledChanged, arg1 == Qt::Checked);
}

QSize CVQTPicker::sizeHint() const {
    return ui->horizontalLayoutWidget->sizeHint();
}

QSize CVQTPicker::minimumSizeHint() const {
    return ui->horizontalLayoutWidget->minimumSizeHint();
}

void CVQTPicker::hideEnabled() {
    QSizePolicy szPol = ui->enabledCheckbox->sizePolicy();
    szPol.setRetainSizeWhenHidden(true);
    ui->enabledCheckbox->setSizePolicy(szPol);
    ui->enabledCheckbox->setHidden(true);
}

CVQTPicker::~CVQTPicker()
{
    delete ui;
}
