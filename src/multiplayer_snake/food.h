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
private:
    GameField * fieldPtr;
    int posX;
    int posY;
};

#endif // FOOD_H
