/*
* Created by Zeng Yinuo, 2021.08.23
*/

#include "MainWindow.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
