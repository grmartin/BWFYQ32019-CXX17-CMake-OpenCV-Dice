//
// Created by Glenn R. Martin on 2019-05-17.
//

#ifndef CVDICE_MAINWINDOWLISTCOLDELEGATE_H
#define CVDICE_MAINWINDOWLISTCOLDELEGATE_H

#include <QListWidgetItem>
#include <QStyledItemDelegate>
#include "MainWindow.h"
#include "ui_mainwindow.h"

class MainWindowListColDelegate: public QStyledItemDelegate {
    Q_OBJECT;

private:
    MainWindow* window;

public:
    explicit MainWindowListColDelegate(MainWindow* window) {
        this->window = window;
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QStyledItemDelegate::paint(painter, option, index);
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        auto sz = window->ui->toolbarList->size();

        sz.setHeight(41);

        return sz;
    }
};

#endif //CVDICE_MAINWINDOWLISTCOLDELEGATE_H
