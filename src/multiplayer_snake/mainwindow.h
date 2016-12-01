#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "snake.h"
#include <gamefield.h>
#include <QMainWindow>
class Snake;
class GameField;
namespace Ui {
class MainWindow;
}
//class Snake;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    Snake * snake;
    GameField * view;
protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_pushButton_clicked();
public slots:
    void restoreFocus();
};


#endif // MAINWINDOW_H
