#include "snake.h"
#include "snaketimer.h"

Snake::Snake(GameField * fieldPtr,direction _direction)
{
      field = fieldPtr;
      blocks.push_back(*(new SnakeBlock(5,5,UP)));
      blocks.push_back(*(new SnakeBlock(5,6,UP)));
      blocks.push_back(*(new SnakeBlock(5,7,UP)));
      field->drawSnakeBlock(5,5,true);
      field->drawSnakeBlock(5,6,true);
      field->drawSnakeBlock(5,7,true);
      currentMoveDirection = _direction;
      SnakeTimer * timer = new SnakeTimer(this);
      timer->start();

}
Snake::~Snake()
{
        while (!blocks.empty()) {
            SnakeBlock * current = &(blocks.back());
            delete current;
            blocks.pop_back();
        }
}
void Snake::changeDirection(direction newDirection){
    currentMoveDirection = newDirection;
    blocks.at(0).neighbourDirection = newDirection;
}

void Snake::moveForward()
{
        if (!field->connected)
            return;
        if (!field->isClient()){ // server

        if (dead) return;
        if ((blocks.front().xPos >= field->xSize-1 && currentMoveDirection == RIGHT) ||
           (blocks.front().xPos <= 0 && currentMoveDirection == LEFT) ||
           (blocks.front().yPos >= field->ySize-1 && currentMoveDirection == DOWN) ||
           (blocks.front().yPos <= 0 && currentMoveDirection == UP))
        {
            dead = true;
            return;
        }
        int x,y,lastX,lastY;
        lastX = x = blocks.back().xPos;
        lastY = y = blocks.back().yPos;
        field->drawSnakeBlock(x,y,false);
        unsigned int i=1;
        blocks.at(0).move(blocks.at(0).neighbourDirection);
        while (i<blocks.size()){
            blocks.at(i).move(blocks.at(i).neighbourDirection);
            blocks.at(i).updateNeighbourDirection(blocks.at(i-1));
            i++;
        }
        x = blocks.front().xPos;
        y = blocks.front().yPos;
        if (outOfBoundaries()) return;
        field->drawSnakeBlock(x,y,true); // end of snake move

        field->server->pushCommand(directionToCmd(currentMoveDirection));

        if (field->food->collide(x,y)) {
            x = blocks.back().xPos;
            y = blocks.back().yPos;
            blocks.push_back(*(new SnakeBlock(lastX,lastY,blocks.back().neighbourDirection)));
            field->drawSnakeBlock(lastX,lastY,true);
            field->food->move();
        }
       } else { //client
            commands currentCmd = field->client->getCommand();
            bool isDirection = commandHandler(currentCmd);
            if (isDirection){
                changeDirection(cmdToDirection(currentCmd,currentMoveDirection));
            }
            if (dead) return;
            changeDirection( cmdToDirection( field->client->getCommand(),currentMoveDirection));
            if ((blocks.front().xPos >= field->xSize-1 && currentMoveDirection == RIGHT) ||
               (blocks.front().xPos <= 0 && currentMoveDirection == LEFT) ||
               (blocks.front().yPos >= field->ySize-1 && currentMoveDirection == DOWN) ||
               (blocks.front().yPos <= 0 && currentMoveDirection == UP))
            {
                dead = true;
                return;
            }
            int x,y,lastX,lastY;
            lastX = x = blocks.back().xPos;
            lastY = y = blocks.back().yPos;
            field->drawSnakeBlock(x,y,false);
            unsigned int i=1;
            blocks.at(0).move(blocks.at(0).neighbourDirection);
            while (i<blocks.size()){
                blocks.at(i).move(blocks.at(i).neighbourDirection);
                blocks.at(i).updateNeighbourDirection(blocks.at(i-1));
                i++;
            }
            x = blocks.front().xPos;
            y = blocks.front().yPos;
            if (outOfBoundaries()) return;
            field->drawSnakeBlock(x,y,true); // end of snake move



            if (field->food->collide(x,y)) {
                x = blocks.back().xPos;
                y = blocks.back().yPos;
                blocks.push_back(*(new SnakeBlock(lastX,lastY,blocks.back().neighbourDirection)));
                field->drawSnakeBlock(lastX,lastY,true);
                field->food->move();
            }
       }

    }
 bool Snake::outOfBoundaries(){
     int x,y;
     x = blocks.front().xPos;
     y = blocks.front().yPos;
     if (x<0 || x>field->xSize || y<0 || y>field->ySize)
         return true;
     else
         return false;
 }

bool Snake::commandHandler(commands cmd){
    switch (cmd) {
    case START: {
            dead = false;
            return false;
        }
     default: return true;
    }
}

commands Snake::directionToCmd(direction dir){
    switch (dir) {
        case UP:return MOVEUP;
        case DOWN:return MOVEDOWN;
        case LEFT:return MOVELEFT;
        case RIGHT:return MOVERIGHT;
    }
}

const direction Snake::cmdToDirection(commands cmd,const direction current){
    switch (cmd) {
        case MOVEUP:return UP;
        case MOVEDOWN:return DOWN;
        case MOVELEFT:return LEFT;
        case MOVERIGHT:return RIGHT;
        default : return current;
    }
}

void Snake::start(){
    dead = false;
    if (!field->isClient() && field->connected){
        field->server->pushCommand(START);
    }
}
