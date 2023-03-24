#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //widget窗口全覆盖
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

