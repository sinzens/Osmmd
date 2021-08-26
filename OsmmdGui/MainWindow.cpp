/*
* Created by Zeng Yinuo, 2021.08.23
*/

#include "MainWindow.h"
#include "stdafx.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    this->InitConnections();
}

void MainWindow::InitConnections()
{
    connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
}
