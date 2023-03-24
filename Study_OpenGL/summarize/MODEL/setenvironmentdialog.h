#ifndef SETENVIRONMENTDIALOG_H
#define SETENVIRONMENTDIALOG_H

#include <QDialog>

namespace Ui {
class setEnvironmentDialog;
}

class setEnvironmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit setEnvironmentDialog(QWidget *parent = nullptr);
    ~setEnvironmentDialog();

    enum EnvironmentType{DESERT,FACTTORY,HORROR,BIOCHEMICALLAB};
    EnvironmentType getMyEnvironment() const;
    void setDialogLable(EnvironmentType environment);   //选择框首选显示的value值

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::setEnvironmentDialog *ui;
    EnvironmentType myEnvironment;
};

#endif // SETENVIRONMENTDIALOG_H
