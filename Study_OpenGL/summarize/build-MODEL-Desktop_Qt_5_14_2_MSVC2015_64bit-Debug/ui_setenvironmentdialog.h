/********************************************************************************
** Form generated from reading UI file 'setenvironmentdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETENVIRONMENTDIALOG_H
#define UI_SETENVIRONMENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_setEnvironmentDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *setEnvironmentDialog)
    {
        if (setEnvironmentDialog->objectName().isEmpty())
            setEnvironmentDialog->setObjectName(QString::fromUtf8("setEnvironmentDialog"));
        setEnvironmentDialog->resize(400, 92);
        verticalLayout = new QVBoxLayout(setEnvironmentDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(setEnvironmentDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(setEnvironmentDialog);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(setEnvironmentDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(setEnvironmentDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), setEnvironmentDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), setEnvironmentDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(setEnvironmentDialog);
    } // setupUi

    void retranslateUi(QDialog *setEnvironmentDialog)
    {
        setEnvironmentDialog->setWindowTitle(QCoreApplication::translate("setEnvironmentDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("setEnvironmentDialog", "\351\200\211\346\213\251\347\216\257\345\242\203", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("setEnvironmentDialog", "\346\262\231\346\274\240", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("setEnvironmentDialog", "\345\267\245\345\216\202", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("setEnvironmentDialog", "\346\201\220\346\200\226", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("setEnvironmentDialog", "\347\224\237\345\214\226\345\256\236\351\252\214\345\256\244", nullptr));

    } // retranslateUi

};

namespace Ui {
    class setEnvironmentDialog: public Ui_setEnvironmentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETENVIRONMENTDIALOG_H
