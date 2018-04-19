#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QLinearGradient>
#include <QPainter>

class Brick : public QGraphicsRectItem
{
public:
    Brick(qreal x, qreal y, qreal width, qreal height,QColor col, QGraphicsItem * parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *) override
    {
        QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, secondColor);
        painter->fillRect(rect(), gradient);
    }
private:
    QColor secondColor;
};

#endif // BRICK_H
