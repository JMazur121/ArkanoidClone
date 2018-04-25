#ifndef PADDLE_H
#define PADDLE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPointF>
#include <QColor>
#include <QBrush>

#include "types.h"

class Paddle : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF paddlePos READ currentPosition WRITE setPosition)
public:
    explicit Paddle(qreal x, qreal y, qreal width, qreal height, QBrush br, QObject *parent = nullptr);

    QPointF currentPosition() const {return position;}
    void setPosition(const QPointF & pos)
    {
        if(pos != position)
        {
            position = pos;
            setPos(pos);
        }
    }
    qreal getWidth() const {return boundingRect().width();}
    qreal getHeight() const {return boundingRect().height();}

    enum paddleMovement{
        None,
        Left,
        Right
    };

    Paddle::paddleMovement getMovement() const {return movement;}
public slots:
    void setMovement(Paddle::paddleMovement p) {movement = p;}
private:
    QPointF position;
    QBrush pBrush;
    paddleMovement movement;
};

#endif // PADDLE_H
