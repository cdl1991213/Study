#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //让widget界面布满MAINWINDOW窗口
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

