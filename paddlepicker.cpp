#include "paddlepicker.h"
#include <QLinearGradient>

PaddlePicker::PaddlePicker(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent), s(scene)
{
    s->setBackgroundBrush(QBrush(QColor(255,255,255)));
    ri = new QGraphicsRectItem(0,25,100,50);
    QBrush b = ri->brush();
    b.setStyle(Qt::NoBrush);
    b.setColor(QColor(100,100,100));
    ri->setBrush(b);
    s->addItem(ri);
    style = 0;
    userColor = QColor(100,100,100);
}

QColor PaddlePicker::getColor() const
{
    return userColor;
}

QBrush PaddlePicker::getSelectedBrush() const
{
    return ri->brush();
}

void PaddlePicker::updateColor(QColor newColor)
{
    userColor = newColor;
    QBrush b = ri->brush();
    if(style == 15){
        QLinearGradient gradient(QPointF(0,25),QPointF(100,75));
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, userColor);
        ri->setBrush(gradient);
        return;
    }
    b.setColor(newColor);
    ri->setBrush(b);
}

void PaddlePicker::setBrush(int val)
{
    style = val;
    QBrush b = ri->brush();
    b.setColor(userColor);
    if(val < 15)
    {
        b.setStyle(static_cast<Qt::BrushStyle>(val));
        ri->setBrush(b);
    }
    else
    {
        QLinearGradient gradient(QPointF(0,25),QPointF(100,75));
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, userColor);
        ri->setBrush(gradient);
    }
}
