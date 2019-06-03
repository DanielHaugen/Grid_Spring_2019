#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void digit_pressed();
    void on_comboBox_currentIndexChanged(); //Originally had - int index - as a parameter
    void on_pushButton_Clear_Radios_released();
    void radio_pressed();
    void adjust_Obj_Counts(bool isCheckAdd);
    void on_pushButton_Clear_Grid_released();
    void on_pushButton_Expand_Collapse_released();
};

#endif // MAINWINDOW_H
