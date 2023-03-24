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

//画一个矩形
void MainWindow::on_action_rect_triggered()
{
    //传入枚举量Shape{None, Rect, Circle, Triangle}
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Rect);
}

//画一个三角形
void MainWindow::on_action_triangle_triggered()
{
    //传入枚举量Shape{None, Rect, Circle, Triangle}
    ui->openGLWidget->drawShape(cdlOpenGLWidget::Triangle);
}

//清空图形
void MainWindow::on_action_clear_triggered()
{
    ui->openGLWidget->drawShape(cdlOpenGLWidget::None);
}

//线框模式
void MainWindow::on_action_wireframe_triggered()
{
    ui->openGLWidget->setWireMode(ui->action_wireframe->isChecked());
}
