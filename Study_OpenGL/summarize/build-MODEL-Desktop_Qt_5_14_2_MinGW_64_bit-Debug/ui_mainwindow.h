/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
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
    QAction *action_triangle;
    QAction *action_rectangle;
    QAction *action_3D_1;
    QAction *action_clear;
    QAction *action_setWireFrame;
    QAction *action_rectangle2;
    QAction *action_3D_2;
    QAction *action_setEnvironment;
    QAction *action_Model_1;
    QWidget *centralwidget;
    cdlOpenGLWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(959, 676);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../summarize/summarize_01_2D/images/rabbit.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background-color:rgb(170, 170, 127);\n"
"	color:rgb(0, 0, 0);\n"
"	font:10pt \"\345\271\274\345\234\206\";\n"
"}\n"
"\n"
"QMenuBar{\n"
"	background-color:rgb(152, 170, 132);\n"
"	color:rgb(60, 60, 60);\n"
"}\n"
"\n"
"QToolBar{\n"
"	background-color:rgb(152, 170, 132);\n"
"}\n"
"\n"
"QAction:checked{\n"
"	background-color:rgb(150, 150, 150);\n"
"}\n"
""));
        action_triangle = new QAction(MainWindow);
        action_triangle->setObjectName(QString::fromUtf8("action_triangle"));
        action_rectangle = new QAction(MainWindow);
        action_rectangle->setObjectName(QString::fromUtf8("action_rectangle"));
        action_3D_1 = new QAction(MainWindow);
        action_3D_1->setObjectName(QString::fromUtf8("action_3D_1"));
        action_clear = new QAction(MainWindow);
        action_clear->setObjectName(QString::fromUtf8("action_clear"));
        action_setWireFrame = new QAction(MainWindow);
        action_setWireFrame->setObjectName(QString::fromUtf8("action_setWireFrame"));
        action_setWireFrame->setCheckable(true);
        action_rectangle2 = new QAction(MainWindow);
        action_rectangle2->setObjectName(QString::fromUtf8("action_rectangle2"));
        action_3D_2 = new QAction(MainWindow);
        action_3D_2->setObjectName(QString::fromUtf8("action_3D_2"));
        action_setEnvironment = new QAction(MainWindow);
        action_setEnvironment->setObjectName(QString::fromUtf8("action_setEnvironment"));
        action_Model_1 = new QAction(MainWindow);
        action_Model_1->setObjectName(QString::fromUtf8("action_Model_1"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new cdlOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(200, 130, 501, 331));
        openGLWidget->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 959, 18));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menubar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menubar->addAction(menu_4->menuAction());
        toolBar->addAction(action_clear);
        toolBar->addAction(action_triangle);
        toolBar->addAction(action_rectangle);
        toolBar->addAction(action_rectangle2);
        toolBar->addAction(action_3D_1);
        toolBar->addAction(action_3D_2);
        toolBar->addAction(action_Model_1);
        toolBar->addAction(action_setEnvironment);
        toolBar->addAction(action_setWireFrame);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Hello myOpenGL!", nullptr));
        action_triangle->setText(QCoreApplication::translate("MainWindow", "\344\270\211\350\247\222\345\275\242", nullptr));
        action_rectangle->setText(QCoreApplication::translate("MainWindow", "\347\237\251\345\275\2421", nullptr));
        action_3D_1->setText(QCoreApplication::translate("MainWindow", "3D1", nullptr));
        action_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        action_setWireFrame->setText(QCoreApplication::translate("MainWindow", "\347\272\277\346\241\206\346\250\241\345\274\217", nullptr));
        action_rectangle2->setText(QCoreApplication::translate("MainWindow", "\347\237\251\345\275\2422", nullptr));
        action_3D_2->setText(QCoreApplication::translate("MainWindow", "3D2", nullptr));
        action_setEnvironment->setText(QCoreApplication::translate("MainWindow", "\347\216\257\345\242\203\350\256\276\347\275\256", nullptr));
        action_Model_1->setText(QCoreApplication::translate("MainWindow", "\346\250\241\345\236\2131", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        menu_3->setTitle(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267", nullptr));
        menu_4->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
