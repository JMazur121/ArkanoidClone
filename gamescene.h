#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>

#include <ball.h>
#include <brick.h>
#include <paddle.h>

class GameScene : public QGraphicsScene
{
Q_OBJECT
public:
    GameScene(Paddle *p, Ball *b, int x, int y, int width, int height);

    void clearScene();
    void initScene();
private:
    Paddle* paddle;
    Ball* ball;
    QRandomGenerator *randomGenerator;
    int initWidth;
    int initHeight;
};

#endif // GAMESCENE_H
