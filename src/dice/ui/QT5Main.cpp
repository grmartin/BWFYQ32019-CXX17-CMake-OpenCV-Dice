//
// Created by Glenn R. Martin on 2019-05-10.
//

#include "QT5Main.h"
#include "MainWindow.h"

#include <QApplication>
#include <dice/JpegFile.h>

#include "dice/transformers/bases/XformerBase.h"
#include "../transformers/Colorer.h"
#include "../transformers/Thresholder.h"
#include "../transformers/Contouring.h"
#include "../transformers/Edger.h"

int cvdice::ui::QT5Main(int argc, char *argv[], char *envp[], cvdice::JpegFile *jpeg) {
    QApplication app(argc, argv);
    QApplication::setApplicationDisplayName("CVDice");
    MainWindow mainWindow(nullptr);

    auto mainWindowPtr = std::shared_ptr<QMainWindow>(&mainWindow);

    mainWindow.show();

    auto colorer = new transformers::Colorer(jpeg->matrix, 1);
    auto thresholder = new transformers::Thresholder(jpeg->matrix, 3, 218);
    auto edger = new transformers::Edger(jpeg->matrix);
    auto contouring = new transformers::Contouring(jpeg->matrix, 1, 2);

    auto uiAppendToolbarFn = [&mainWindow](CVQTImageToolbar *toolbar) {
        QString name = toolbar->objectName();
        return mainWindow.addToolbar(toolbar, &name);
    };

    edger->enabled = false;

    colorer->showFor(mainWindowPtr, uiAppendToolbarFn);
    thresholder->showFor(mainWindowPtr, uiAppendToolbarFn);
    edger->showFor(mainWindowPtr, uiAppendToolbarFn);
    contouring->showFor(mainWindowPtr, uiAppendToolbarFn);

    CHAIN_XFORMER(colorer, thresholder);
    CHAIN_XFORMER(thresholder, edger);
    CHAIN_XFORMER(edger, contouring);

    colorer->update();

    return QApplication::exec();
}