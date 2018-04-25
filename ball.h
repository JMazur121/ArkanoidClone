#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPointF>
#include <QLinearGradient>
#include <QPainterPath>
#include <QPainter>

#include "types.h"

class Ball : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF ballPos READ currentPosition WRITE setPosition)
    Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged)
public:
    explicit Ball(qreal rad, QObject *parent = nullptr);

    QRectF boundingRect() const { return QRectF(-radius/2, -radius/2, radius, radius); }

    QPointF currentPosition() const {return position;}
    void setPosition(const QPointF & pos)
    {
        if(pos != position)
        {
            position = pos;
            setPos(pos);
        }
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        QPainterPath path;
        QLinearGradient gradient(boundingRect().topLeft(), boundingRect().bottomRight());
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::black);
        painter->setRenderHint(QPainter::Antialiasing,true);
        path.addEllipse(boundingRect());
        painter->fillPath(path,gradient);
    }

    QPainterPath shape() const {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }
    qreal getRadius() const {return radius;}
    qreal x() const
    {
        return pos().x();
    }

    qreal y() const
    {
        return pos().y();
    }

public slots:
    void setX(qreal x)
    {
//        qWarning("Floating point comparison needs context sanity check");
//        if (qFuzzyCompare(m_x, x))
//            return;

//        m_x = x;
        setPos(x, y());
        emit xChanged(x);
    }

    void setY(qreal y)
    {
//        qWarning("Floating point comparison needs context sanity check");
//        if (qFuzzyCompare(m_y, y))
//            return;

        setPos(x(), y);
        emit yChanged(y);
    }

signals:
    void xChanged(qreal x);

    void yChanged(qreal y);

private:
    QPointF position;
    qreal radius;
    qreal m_x;
    qreal m_y;
};
#endif // BALL_H
