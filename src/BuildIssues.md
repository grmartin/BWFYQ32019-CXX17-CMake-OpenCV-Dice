# All

# DEV NOTE: Breakpointing
Clang seems to refuse to breakpoint at times... You can forse it by using the right signal (on x86/64 CPUS):
```c
        __asm__ volatile("int $0x03");
```

# Linux

## STL Comparison and method matching errors for many STL Container classes

Chances are you are using an older version of GCC, GCC 7 or 8 is required for this project. (If you are on a debian-based system, try downloading from Buster's sources)

## std::function is not known

Clang does NOT require the import of `<functional>`, this is a deviation from standard. GCC does.

## AutoUIC error: Could not find "xxx.ui" 

```
[ 65%] Automatic MOC and UIC for target CVDiceQT
AutoUic error
-------------
  "/.../CVDice/src/dice/ui/MainWindowListColDelegate.h"
Could not find "mainwindow.ui" in
  "/.../CVDice/src/dice/ui/mainwindow.ui"
```

Chances are you have a CPP/H file (`MainWindowListColDelegate.h`) importing `ui_mainwindow.h` whilst the file on disk is `MainWindow.ui` (thus generating `ui_MainWindow.h`) and that cannot be found on the filesystem in a case sensitive file system. Windows and Mac are case-insensitive, Linux is not.

## AutoMoc subprocess error: Parse error at "cvdice" (a namespace)

```
AutoMoc subprocess error
------------------------
The moc process failed to compile
  "/.../CVDice/src/dice/ui/widgets/CVQTWidget.h"
into
  "/.../CVDice/src/cmake-build-debug/CVDiceQT_autogen/YIWCZLQDOW/moc_CVQTWidget.cpp".

Command
-------
/usr/lib/x86_64-linux-gnu/qt5/bin/moc -I/.../CVDice/src/cmake-build-debug -I/.../CVDice/src -I/.../CVDice/src/dice/ui -I/.../.hunter/_Base/5a73f91/bb25d6f/3d3a85c/Install/include/opencv4 -I/.../.hunter/_Base/5a73f91/bb25d6f/3d3a85c/Install/include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++-64 -I/usr/include -I/usr/include/c++/6 -I/usr/include/x86_64-linux-gnu/c++/6 -I/usr/include/c++/6/backward -I/usr/lib/gcc/x86_64-linux-gnu/6/include -I/usr/local/include -I/usr/lib/gcc/x86_64-linux-gnu/6/include-fixed -I/usr/include/x86_64-linux-gnu -DBOOST_NO_AUTO_PTR -DCVD_USE_BOOST_FS=1 -DCVD_USE_QT5=1 -DQT_CORE_LIB -DQT_GUI_LIB -DQT_WIDGETS_LIB -o /.../CVDice/src/cmake-build-debug/CVDiceQT_autogen/YIWCZLQDOW/moc_CVQTWidget.cpp /.../CVDice/src/dice/ui/widgets/CVQTWidget.h

Output
------
/.../CVDice/src/dice/ui/widgets/CVQTWidget.h:19: Parse error at "cvdice"
```

Older versions of QT5 like those in Debian dont support concise namespaces... `a::b::c` and they must be destructured or the OS Updated.