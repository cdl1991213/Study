#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //mainwindow的构造函数和析构函数
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_rect_triggered();

    void on_action_clear_triggered();

    void on_action_lineMode_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
