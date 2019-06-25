#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/mat.hpp>
#include <QListWidgetItem>


class CVQTImageToolbar;
constexpr int MainWindowToolbarItemDataRoleIdentifier = 1701;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

protected:
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    QListWidgetItem *addToolbar(QWidget *toolbar, QString *identifier = nullptr);

    void updateMatrix(const cv::Mat &matrix);

    static QObject *findByClassName(const QObject *o, const char *name);

    friend class MainWindowListColDelegate;
};

#endif // MAINWINDOW_H
