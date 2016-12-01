#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H
#include <gamefield.h>
#include <QDialog>
#include "QCloseEvent"
class GameField;
namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();
    void setField(GameField *);
private slots:
    void on_pushButton_clicked();
signals:
    void dialogClosed();
private:
    void closeEvent(QCloseEvent *event);
    Ui::ConnectDialog *ui;
    GameField * field;
};

#endif // CONNECTDIALOG_H
