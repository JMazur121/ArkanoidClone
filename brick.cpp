#include "brick.h"

Brick::Brick(qreal x, qreal y, qreal width, qreal height, QColor col, QGraphicsItem *parent) : QGraphicsRectItem(x,y,width,height,parent),
    secondColor(col)
{

}
