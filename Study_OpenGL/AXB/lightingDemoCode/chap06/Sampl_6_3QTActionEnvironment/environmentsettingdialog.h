#ifndef ENVIRONMENTSETTINGDIALOG_H
#define ENVIRONMENTSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class EnvironmentSettingDialog;
}

class EnvironmentSettingDialog : public QDialog
{
    Q_OBJECT

public:
    enum EnvironmentType{DESERT,FACTTORY,HORROR,BIOCHEMICALLAB};

    explicit EnvironmentSettingDialog(QWidget *parent = 0);
    void setType(EnvironmentType type);
    EnvironmentType type() const;
    ~EnvironmentSettingDialog();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::EnvironmentSettingDialog *ui;
    EnvironmentType m_type;
};

#endif // ENVIRONMENTSETTINGDIALOG_H
