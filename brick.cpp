#include "brick.h"

Brick::Brick(qreal x, qreal y, qreal width, qreal height, QColor col, QGraphicsItem *parent) : QGraphicsRectItem(x,y,width,height,parent),
    secondColor(col)
{
    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, secondColor);
    this->setBrush(gradient);
    this->setData(0,GameBlock);
}
