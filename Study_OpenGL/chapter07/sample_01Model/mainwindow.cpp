#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);   //将widget覆盖整个mainwindow
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_test_triggered()
{
    //---
}
