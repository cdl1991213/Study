#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->openGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actEnvironmentSetting_triggered()
{
    EnvironmentSettingDialog * dlg=new EnvironmentSettingDialog(this);
    dlg->setType(ui->openGLWidget->type());
    if(dlg->exec()==QDialog::Accepted){
        ui->openGLWidget->setEnvironmentType(dlg->type());
    }
    delete dlg;
}
