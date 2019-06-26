#include "MainWindow.h"
#include "MainWindowListColDelegate.h"
#include "ui_MainWindow.h"

#include <dice/ui/widgets/CVQTImageToolbar.h>
#include <dice/ui/widgets/CVQTPicker.h>
#include <QScreen>

QObject *MainWindow::MainWindow::findByClassName(const QObject *const o, const char *name) {
    QObject *res = nullptr;
        foreach (QObject *c, o->children()) {
            if (res) break;

            if (QString::fromLocal8Bit(c->metaObject()->className()) == name) res = c;
            else res = findByClassName(c, name);
        }
    return res;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);

    ui->toolbarList->setItemDelegateForColumn(0, new MainWindowListColDelegate(this));
}

MainWindow::~MainWindow() {
    delete ui;
}

QListWidgetItem *MainWindow::addToolbar(QWidget *toolbar, QString *identifier) {
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
