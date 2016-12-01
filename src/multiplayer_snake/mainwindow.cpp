#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"
#include <connectdialog.h>
#define DEFAULT_FIELD_SIZE 30
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = new GameField(DEFAULT_FIELD_SIZE,DEFAULT_FIELD_SIZE,ui->snakeView);
    this->setFocus();
    //snake = new Snake(view,UP);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete view;
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Up){
        if (view->isClient())
            return;
        view->snake->changeDirection( UP);
    }
    if(event->key() == Qt::Key_Down){
        if (view->isClient())
            return;
        view->snake->changeDirection( DOWN);
    }
    if(event->key() == Qt::Key_Left){
        if (view->isClient())
            return;
        view->snake->changeDirection( LEFT);
    }
    if(event->key() == Qt::Key_Right){
        if (view->isClient())
            return;
        view->snake->changeDirection( RIGHT);
    }
    if(event->key() == Qt::Key_Space){
        if (view->isClient())
            return;
    view->snake->start();
    view->snake->moveForward();
    }
    if(event->key() == Qt::Key_W){
        view->food->moveToDirection(UP);
    }
    if(event->key() == Qt::Key_S){
        view->food->moveToDirection(DOWN);
    }
    if(event->key() == Qt::Key_A){
        view->food->moveToDirection(LEFT);
    }
    if(event->key() == Qt::Key_D){
        view->food->moveToDirection(RIGHT);
    }
}

void MainWindow::on_pushButton_clicked()
{
    ConnectDialog * form = new ConnectDialog();
    form->setField(view);
    form->show();
    form->connect(form,SIGNAL(dialogClosed()),this,SLOT(restoreFocus()));
}

void MainWindow::restoreFocus(){
    this->setFocus();
}
