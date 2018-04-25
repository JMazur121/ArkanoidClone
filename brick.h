#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsRectItem>
#include <QLinearGradient>

#include "types.h"

class Brick : public QGraphicsRectItem
{
public:
    Brick(qreal x, qreal y, qreal width, qreal height,QColor col, QGraphicsItem * parent = 0);
private:
    QColor secondColor;
};

#endif // BRICK_H
