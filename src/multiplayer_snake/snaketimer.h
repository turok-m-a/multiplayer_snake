#ifndef SNAKETIMER_H
#define SNAKETIMER_H
#include <snake.h>
#include <QThread>
class SnakeTimer : public QThread
{
    Q_OBJECT
private:
    Snake * snake;
public:
    SnakeTimer(Snake *);
protected:
    void run();
};

#endif // SNAKETIMER_H
