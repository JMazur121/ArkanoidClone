#include "gamescene.h"

GameScene::GameScene(Paddle *p, Ball *b, int x, int y, int width, int height) : QGraphicsScene(x,y,width,height),paddle(p), ball(b)
{
    this->setBackgroundBrush(QBrush(QColor(214, 214, 194)));
}
