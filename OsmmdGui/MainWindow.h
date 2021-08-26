/*
* Created by Zeng Yinuo, 2021.08.23
*/

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    void InitConnections();

    Ui::MainWindowClass ui;
};
