#include "gamefield.h"

GameField::GameField(int x,int y,QTableWidget * _snakeView){
    xSize = x;
    ySize = y;
    snakeView = _snakeView;
    for (int i=0;i<xSize;i++)
        for (int j=0;j<ySize;j++)
        {
            QTableWidgetItem * ti = new QTableWidgetItem();
            snakeView->setItem(i,j,ti);
        }
    food = new Food(this);
    snake = new Snake(this, UP);
}
GameField::~GameField(){
    for (int i=0;i<xSize;i++)
        for (int j=0;j<ySize;j++)
        {
            QTableWidgetItem * ti = snakeView->item(i,j);
            delete ti;
        }
    delete food;
    delete snake;
    if (connected) {
    if (clientMode)
        delete client;
    else
        delete server;
    }
}

void GameField::setClientAddress(QString address,ushort port){
    client = new Client(address,port);
    clientMode = true;
    client->startThread();
    Sleep(100);
    connected = client->isConnected();

}

void GameField::setServerMode(QString address,ushort port){
    server = new Server(address,port);
    clientMode = false;
    server->startThread();
    connected = server->isConnected();

}

void GameField::drawSnakeBlock(int x,int y,bool blockPresent){
    if (blockPresent)
        snakeView->item(y,x)->setBackgroundColor(QColor("blue"));
    else
        snakeView->item(y,x)->setBackgroundColor(QColor("white"));
    update();
}

void GameField::drawFoodBlock(int x,int y,bool blockPresent){
    if (blockPresent)
        snakeView->item(y,x)->setBackgroundColor(QColor("yellow"));
    else
        snakeView->item(y,x)->setBackgroundColor(QColor("white"));
    update();
}

void GameField::update(){
    snakeView->viewport()->update();
}
 bool GameField::isClient(){
     return clientMode;
 }
