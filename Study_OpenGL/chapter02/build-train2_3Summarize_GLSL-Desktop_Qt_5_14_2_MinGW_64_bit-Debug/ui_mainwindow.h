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
    QAction *action_rect;
    QAction *action_triangle;
    QAction *action_clear;
    QAction *action_wireframe;
    QAction *action_verticalflip;
    QAction *action_horizontaltransverse;
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
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8("C:/Users/ChenDlung/Pictures/Draw&Guess/2021-10-7_23-33-28.png"), QSize(), QIcon::Normal, QIcon::Off);
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
        action_rect = new QAction(MainWindow);
        action_rect->setObjectName(QString::fromUtf8("action_rect"));
        action_triangle = new QAction(MainWindow);
        action_triangle->setObjectName(QString::fromUtf8("action_triangle"));
        action_clear = new QAction(MainWindow);
        action_clear->setObjectName(QString::fromUtf8("action_clear"));
        action_wireframe = new QAction(MainWindow);
        action_wireframe->setObjectName(QString::fromUtf8("action_wireframe"));
        action_wireframe->setCheckable(true);
        action_verticalflip = new QAction(MainWindow);
        action_verticalflip->setObjectName(QString::fromUtf8("action_verticalflip"));
        action_verticalflip->setCheckable(true);
        action_horizontaltransverse = new QAction(MainWindow);
        action_horizontaltransverse->setObjectName(QString::fromUtf8("action_horizontaltransverse"));
        action_horizontaltransverse->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new cdlOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(130, 80, 501, 361));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 18));
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
        toolBar->addAction(action_rect);
        toolBar->addAction(action_triangle);
        toolBar->addAction(action_wireframe);
        toolBar->addAction(action_verticalflip);
        toolBar->addAction(action_horizontaltransverse);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "mySummarize!", nullptr));
        action_rect->setText(QCoreApplication::translate("MainWindow", "\347\224\273\344\270\200\344\270\252\347\237\251\345\275\242", nullptr));
        action_triangle->setText(QCoreApplication::translate("MainWindow", "\347\224\273\344\270\200\344\270\252\344\270\211\350\247\222\345\275\242", nullptr));
        action_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\345\233\276\345\275\242", nullptr));
        action_wireframe->setText(QCoreApplication::translate("MainWindow", "\347\272\277\346\241\206\346\250\241\345\274\217", nullptr));
        action_verticalflip->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\270\213\351\242\240\345\200\222", nullptr));
        action_horizontaltransverse->setText(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\346\250\252\347\247\273", nullptr));
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
