#pragma once
#ifndef SNAKEBLOCK_H
#define SNAKEBLOCK_H
#include <direction.h>

class SnakeBlock
{
public:
    int xPos;
    int yPos;
    void updateNeighbourDirection(const SnakeBlock & nextBlock);
    direction neighbourDirection;
    SnakeBlock(int x,int y,direction nextBlockDirection)
    {
        xPos=x;
        yPos=y;
        neighbourDirection = nextBlockDirection;
    }
    void move(direction dir){
        switch (dir) {
        case UP: {
            yPos--;
            return;
        }
        case DOWN: {
            yPos++;
            return;
        }
        case RIGHT: {
            xPos++;
            return;
        }
        case LEFT: {
            xPos--;
            return;
        }
        }

    }
    direction getOppositeDirection(){
        switch (neighbourDirection){
        case UP : return DOWN;
        case DOWN : return UP;
        case LEFT : return RIGHT;
        case RIGHT : return LEFT;
        }
        return DOWN;
    }
};

#endif // SNAKEBLOCK_H
