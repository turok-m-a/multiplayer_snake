#include "snakeblock.h"
void SnakeBlock::updateNeighbourDirection(const SnakeBlock & nextBlock){
    if (nextBlock.xPos - this->xPos == -1) {
        this->neighbourDirection = LEFT;
    }
    if (nextBlock.xPos - this->xPos == 1) {
        this->neighbourDirection = RIGHT;
    }
    if (nextBlock.yPos - this->yPos == -1 &&
            nextBlock.xPos - this->xPos == 0) {
        this->neighbourDirection = UP;
    }
    if (nextBlock.yPos - this->yPos == 1 &&
            nextBlock.xPos - this->xPos == 0) {
        this->neighbourDirection = DOWN;
    }
}


