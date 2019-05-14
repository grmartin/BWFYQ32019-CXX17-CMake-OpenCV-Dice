#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dice/ui/widgets/CVQTImageToolbar.h>
#include <opencv2/core/mat.hpp>
#include <QListWidgetItem>

constexpr int MainWindowToolbarItemDataRoleIdentifier = 1701;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    QListWidgetItem *addToolbar(CVQTImageToolbar *toolbar, QString *identifier = nullptr);

    void updateMatrix(const cv::Mat &matrix);

};

#endif // MAINWINDOW_H
