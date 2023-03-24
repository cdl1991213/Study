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
    QAction *action_clear;
    QAction *action_rect;
    QAction *action_triangle;
    QAction *action_setWireFrame;
    QAction *action_rect_tecture;
    QAction *action_rect_tecture_dynamic;
    QAction *action_3D;
    QAction *action_3D_Rotate;
    QWidget *centralwidget;
    cdlOpenGLWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
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
        action_clear = new QAction(MainWindow);
        action_clear->setObjectName(QString::fromUtf8("action_clear"));
        action_rect = new QAction(MainWindow);
        action_rect->setObjectName(QString::fromUtf8("action_rect"));
        action_triangle = new QAction(MainWindow);
        action_triangle->setObjectName(QString::fromUtf8("action_triangle"));
        action_setWireFrame = new QAction(MainWindow);
        action_setWireFrame->setObjectName(QString::fromUtf8("action_setWireFrame"));
        action_setWireFrame->setCheckable(true);
        action_rect_tecture = new QAction(MainWindow);
        action_rect_tecture->setObjectName(QString::fromUtf8("action_rect_tecture"));
        action_rect_tecture_dynamic = new QAction(MainWindow);
        action_rect_tecture_dynamic->setObjectName(QString::fromUtf8("action_rect_tecture_dynamic"));
        action_3D = new QAction(MainWindow);
        action_3D->setObjectName(QString::fromUtf8("action_3D"));
        action_3D_Rotate = new QAction(MainWindow);
        action_3D_Rotate->setObjectName(QString::fromUtf8("action_3D_Rotate"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        openGLWidget = new cdlOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(220, 140, 300, 200));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 18));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        toolBar->addAction(action_clear);
        toolBar->addAction(action_rect);
        toolBar->addAction(action_rect_tecture);
        toolBar->addAction(action_rect_tecture_dynamic);
        toolBar->addAction(action_triangle);
        toolBar->addAction(action_setWireFrame);
        toolBar->addAction(action_3D);
        toolBar->addAction(action_3D_Rotate);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\345\233\276\345\275\242", nullptr));
        action_rect->setText(QCoreApplication::translate("MainWindow", "\347\237\251\345\275\242", nullptr));
        action_triangle->setText(QCoreApplication::translate("MainWindow", "\344\270\211\350\247\222\345\275\242", nullptr));
        action_setWireFrame->setText(QCoreApplication::translate("MainWindow", "\347\272\277\346\241\206\346\250\241\345\274\217", nullptr));
        action_rect_tecture->setText(QCoreApplication::translate("MainWindow", "\347\272\271\347\220\206\347\237\251\345\275\242", nullptr));
#if QT_CONFIG(tooltip)
        action_rect_tecture->setToolTip(QCoreApplication::translate("MainWindow", "\347\272\271\347\220\206\347\237\251\345\275\242", nullptr));
#endif // QT_CONFIG(tooltip)
        action_rect_tecture_dynamic->setText(QCoreApplication::translate("MainWindow", "\345\212\250\346\200\201\347\272\271\347\220\206\347\237\251\351\230\265", nullptr));
        action_3D->setText(QCoreApplication::translate("MainWindow", "3D", nullptr));
        action_3D_Rotate->setText(QCoreApplication::translate("MainWindow", "\346\227\213\350\275\2543D", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
