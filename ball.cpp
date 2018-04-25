#include "ball.h"

Ball::Ball(qreal rad, QObject *parent) : QObject(parent), QGraphicsItem(), radius(rad)
{
    this->setData(0,GameBall);
}
