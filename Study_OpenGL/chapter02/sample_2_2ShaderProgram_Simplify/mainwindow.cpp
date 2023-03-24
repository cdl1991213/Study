#include "mainwindow.h"
#include "ui_mainwindow.h"

//mainwindow的构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

//mainwindow的析构函数
MainWindow::~MainWindow()
{
    delete ui;
}

//画一个矩形
void MainWindow::on_action_rect_triggered()
{
    //传入枚举量Shape{None, Rect, Circle, Triangle}
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Rect);
}

//清空图形
void MainWindow::on_action_clear_triggered()
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::None);
}

//线框模式
void MainWindow::on_action_lineMode_triggered()
{
    ui->openGLWidget->setWireMode(ui->action_lineMode->isChecked());
}
