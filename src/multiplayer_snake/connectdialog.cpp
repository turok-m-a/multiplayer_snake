#include "connectdialog.h"
#include "ui_connectdialog.h"
#include "server.h"
#include "client.h"
ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    ui->serverButton->setChecked(true);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_pushButton_clicked()
{
    if (ui->serverButton->isChecked()){
        field->setServerMode(QString(LISTEN_ANY),GAME_PORT);

    }
    if (ui->clientButton->isChecked()){
        field->setClientAddress(QString(ui->lineEdit->text()),GAME_PORT);

    }
}

void ConnectDialog::setField(GameField * _field){
    field = _field;
}

void ConnectDialog::closeEvent(QCloseEvent *event)
{
    emit dialogClosed();
    event->accept();
}
