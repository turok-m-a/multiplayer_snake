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
    if(!fieldPtr->isClient()) return;
    srand(time(NULL));
    posX = rand() % fieldPtr->xSize;
    posY = rand() % fieldPtr->ySize;
    fieldPtr->drawFoodBlock(posX,posY,true);
    if (fieldPtr->isClient()){
        fieldPtr->client->pushCommand(COORDINATES);
        fieldPtr->client->pushCommand((commands)(posX+COORD_CMD));
        fieldPtr->client->pushCommand((commands)(posY+COORD_CMD));
    }
}

void Food::moveToPosition(int x,int y){
    fieldPtr->drawFoodBlock(x,y,false);
    posX = x;
    posY = y;
    fieldPtr->drawFoodBlock(posX,posY,true);
}

void Food::moveToDirection(direction dir){
    if (!fieldPtr->connected) return;

  switch(dir){
    case LEFT: {
        if (posX == 1) return;
        fieldPtr->drawFoodBlock(posX,posY,false);
        posX--;
        fieldPtr->drawFoodBlock(posX,posY,true);
        if (fieldPtr->isClient()){
            fieldPtr->client->pushCommand(MOVELEFT);
        }
        break;
    }
    case RIGHT: {
      if (posX == fieldPtr->xSize - 1) return;
        fieldPtr->drawFoodBlock(posX,posY,false);
        posX++;
        fieldPtr->drawFoodBlock(posX,posY,true);
        if (fieldPtr->isClient()){
            fieldPtr->client->pushCommand(MOVERIGHT);
        }
        break;
    }
    case UP: {
      if (posY == 1) return;
        fieldPtr->drawFoodBlock(posX,posY,false);
        posY--;
        fieldPtr->drawFoodBlock(posX,posY,true);
        if (fieldPtr->isClient()){
            fieldPtr->client->pushCommand(MOVEUP);
        }
        break;
    }
    case DOWN: {
      if (posY == fieldPtr->ySize - 1) return;
        fieldPtr->drawFoodBlock(posX,posY,false);
        posY++;
        fieldPtr->drawFoodBlock(posX,posY,true);
        if (fieldPtr->isClient()){
            fieldPtr->client->pushCommand(MOVEDOWN);
        }
        break;
    }
    default:break;
  }
}
