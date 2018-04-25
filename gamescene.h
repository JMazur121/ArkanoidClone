#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QRandomGenerator>

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
    void initPaddle();
    void initBall();
    void setBallInitPos();
    void destroyBrick(Brick* b);
    Paddle* getPadlle() {return paddle;}
    Ball* getBall() {return ball;}
    qreal getPaddleHLevel() const {return paddleHLevel;}
    int getInitWidth() const {return initWidth;}
private:
    Paddle* paddle;
    Ball* ball;
    int initWidth;
    int initHeight;
    qreal paddleHLevel;
    int currentBricksNumber;
signals:
    void sceneInitialized();
    void allBricksDestroyed();
};

#endif // GAMESCENE_H
