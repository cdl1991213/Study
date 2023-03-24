﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triangle_triggered();

    void on_action_rectangle_triggered();

    void on_action_3D_1_triggered();

    void on_action_clear_triggered();

    void on_action_setWireFrame_triggered();

    void on_action_rectangle2_triggered();

    void on_action_3D_2_triggered();

    void on_action_setEnvironment_triggered();

    void on_action_Model_1_triggered();

    void on_action_loadModel_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
