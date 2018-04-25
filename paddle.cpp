#include "paddle.h"

Paddle::Paddle(qreal x, qreal y, qreal width, qreal height,QBrush br, QObject *parent) : QObject(parent), QGraphicsRectItem(x,y,width,height),
    pBrush(br)
{
    this->setBrush(br);
    movement = None;
    this->setData(0,GamePaddle);
}
