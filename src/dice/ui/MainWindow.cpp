#include "MainWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

QListWidgetItem *MainWindow::addToolbar(CVQTImageToolbar *toolbar, QString *identifier) {
    auto item = new QListWidgetItem(ui->toolbarList);
    ui->toolbarList->addItem(item);
    item->setSizeHint(toolbar->sizeHint());
    ui->toolbarList->setItemWidget(item, toolbar);
    ui->toolbarList->update();
    if (identifier != nullptr) {
        QVariant qvarName(*identifier);
        item->setData(MainWindowToolbarItemDataRoleIdentifier, qvarName);
    }
    return item;
}

void MainWindow::updateMatrix(const cv::Mat &matrix) {
    ui->renderArea->paintMatrix(matrix);
}
