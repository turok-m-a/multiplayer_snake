#pragma once
#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#include <mainwindow.h>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>
#include <food.h>
#include <client.h>
#include <server.h>
using namespace std;
class Food;
class Snake;
class GameField
{
    friend class Snake;
    friend class MainWindow;
    friend class Food;
public:
    GameField(int x,int y,QTableWidget * _snakeView);
    ~GameField();
    void drawSnakeBlock(int x,int y,bool blockPresent);
    int xSize,ySize;
    void update();
    void drawFoodBlock(int x, int y, bool blockPresent);
    void setClientAddress(QString,ushort);
    void setServerMode(QString,ushort);
    bool isClient();
    bool isConnected();
    bool gameOver = false;
private:
    bool clientMode;
    int connected = 0;
    QTableWidget * snakeView;
    Food * food;
    Snake * snake;
    Server * server;
    Client * client;
};

#endif // GAMEFIELD_H
