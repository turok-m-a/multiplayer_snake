#include "food.h"
#include "time.h"
#include "direction.h"
Food::Food(GameField * ptr)
{
    fieldPtr = ptr;
    do {
    posX = rand() % fieldPtr->xSize;
    posY = rand() % fieldPtr->ySize;
    } while (posX == 5 && (posY>=5 && posY <= 7)); // dont place food at snake initial posotion
    fieldPtr->drawFoodBlock(posX,posY,true);
}

bool Food::collide(int snakeHeadX, int snakeHeadY){
    if (snakeHeadX == posX && snakeHeadY == posY){
        return true;
    } else {
        return false;
    }
}

void Food::move(){
    srand(time(NULL));
    posX = rand() % fieldPtr->xSize;
    posY = rand() % fieldPtr->ySize;
    fieldPtr->drawFoodBlock(posX,posY,true);

}

void Food::moveToDirection(direction dir){
  switch(dir){
    case LEFT: {
        fieldPtr->drawFoodBlock(posX,posY,false);
        posX--;
        fieldPtr->drawFoodBlock(posX,posY,true);
        break;
    }
    case RIGHT: {
        fieldPtr->drawFoodBlock(posX,posY,false);
        posX++;
        fieldPtr->drawFoodBlock(posX,posY,true);
        break;
    }
    case UP: {
        fieldPtr->drawFoodBlock(posX,posY,false);
        posY--;
        fieldPtr->drawFoodBlock(posX,posY,true);
        break;
    }
    case DOWN: {
        fieldPtr->drawFoodBlock(posX,posY,false);
        posY++;
        fieldPtr->drawFoodBlock(posX,posY,true);
        break;
    }
  }
}
