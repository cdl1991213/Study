/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <cdlopenglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_rect;
    QAction *action_clear;
    QAction *action_lineMode;
    QWidget *centralwidget;
    cdlOpenGLWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(788, 554);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background-color:rgb(68, 68, 68);\n"
"	color:rgb(255, 255, 255);\n"
"	font:10pt \"\345\271\274\345\234\206\";\n"
"}\n"
"\n"
"QMenuBar{\n"
"	background-color:rgb(200, 200, 200);\n"
"	color:rgb(60, 60, 60);\n"
"}\n"
"\n"
"QToolBar{\n"
"	background-color:rgb(150, 150, 150);\n"
"}\n"
"\n"
"QAction:checked{\n"
"	background-color:rgb(150, 150, 150);\n"
"}\n"
""));
        action_rect = new QAction(MainWindow);
        action_rect->setObjectName(QStringLiteral("action_rect"));
        action_clear = new QAction(MainWindow);
        action_clear->setObjectName(QStringLiteral("action_clear"));
        action_lineMode = new QAction(MainWindow);
        action_lineMode->setObjectName(QStringLiteral("action_lineMode"));
        action_lineMode->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        openGLWidget = new cdlOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(200, 110, 300, 200));
        openGLWidget->setStyleSheet(QStringLiteral(""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 788, 18));
        menu = new QMenu(menubar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        toolBar->addAction(action_clear);
        toolBar->addAction(action_rect);
        toolBar->addAction(action_lineMode);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "hello demo2!", Q_NULLPTR));
        action_rect->setText(QApplication::translate("MainWindow", "\347\224\273\344\270\200\344\270\252\347\237\251\345\275\242", Q_NULLPTR));
        action_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\345\233\276\345\275\242", Q_NULLPTR));
        action_lineMode->setText(QApplication::translate("MainWindow", "\347\272\277\346\241\206\346\250\241\345\274\217", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\345\274\200\345\247\213", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
