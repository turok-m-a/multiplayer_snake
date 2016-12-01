#include "snaketimer.h"
SnakeTimer::SnakeTimer(Snake * _snake)
{
    snake = _snake;
}
void SnakeTimer::run(){
    while (true) {
        if (!snake->field->gameOver) {
        snake->moveForward();
        //snake->field->update();
        Sleep(snake->moveInterval);
        }
        Sleep(100);
    }
}
