#ifndef FOOD_H
#define FOOD_H
#include <gamefield.h>
class GameField;
class Food
{
public:
    Food(GameField *);
    bool collide(int, int);
    void move();
    void moveToDirection(direction);
    void moveToPosition(int x,int y);
private:
    GameField * fieldPtr;
    int posX;
    int posY;
};

#endif // FOOD_H
