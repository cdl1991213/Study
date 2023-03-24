#include "setenvironmentdialog.h"
#include "ui_setenvironmentdialog.h"

setEnvironmentDialog::setEnvironmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setEnvironmentDialog)
{
    ui->setupUi(this);
}

setEnvironmentDialog::~setEnvironmentDialog()
{
    delete ui;
}

setEnvironmentDialog::EnvironmentType setEnvironmentDialog::getMyEnvironment() const
{
    return myEnvironment;
}

void setEnvironmentDialog::on_comboBox_currentIndexChanged(int index)   //选择环境
{
    myEnvironment = (EnvironmentType)index;
}

void setEnvironmentDialog::setDialogLable(setEnvironmentDialog::EnvironmentType environment)    //选择框首选显示的value值
{
    ui->comboBox->setCurrentIndex((int)environment);
}
