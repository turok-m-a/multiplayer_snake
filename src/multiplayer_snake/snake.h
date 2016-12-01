#ifndef SNAKE_H
#define SNAKE_H
#include <direction.h>
#include <deque>
#include "gamefield.h"
#include <snakeblock.h>
#include <iterator>
#include <windows.h>
#include "commands.h"
using namespace std;
class GameField;
class Snake
{
public:
    Snake(){}
    Snake(GameField * fieldPtr,direction);
    int moveInterval = 400;
    ~Snake();
    void changeDirection(direction);
    bool dead = true;
    void moveForward();
    GameField * field;
    void start();
private:
    bool commandHandler(commands cmd);
    commands directionToCmd(direction dir);
    const direction cmdToDirection(commands cmd,const direction current);
    bool outOfBoundaries();
    std::deque<SnakeBlock> blocks;
    direction currentMoveDirection;
};

#endif // SNAKE_H
