#include "environmentsettingdialog.h"
#include "ui_environmentsettingdialog.h"

EnvironmentSettingDialog::EnvironmentSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnvironmentSettingDialog)
{
    ui->setupUi(this);
}

void EnvironmentSettingDialog::setType(EnvironmentSettingDialog::EnvironmentType type)
{
    ui->comboBox->setCurrentIndex((int)type);
}

EnvironmentSettingDialog::EnvironmentType EnvironmentSettingDialog::type() const
{
    return m_type;
}

EnvironmentSettingDialog::~EnvironmentSettingDialog()
{
    delete ui;
}

void EnvironmentSettingDialog::on_comboBox_currentIndexChanged(int index)
{
    m_type=(EnvironmentType)index;
}
