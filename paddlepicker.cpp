#include "paddlepicker.h"
#include <QLinearGradient>

PaddlePicker::PaddlePicker(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent), s(scene)
{
    s->setBackgroundBrush(QBrush(QColor(255,255,255)));
    ri = new QGraphicsRectItem(0,25,100,50);
    ri->setBrush(Qt::SolidPattern);
    s->addItem(ri);
    style = 1;
}

QColor PaddlePicker::getColor() const
{
    return userColor;
}

void PaddlePicker::updateColor(QColor newColor)
{
    userColor = newColor;
    QBrush b = ri->brush();
    if(style == 4){
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
    switch (val) {
    case 1:
        b.setStyle(Qt::SolidPattern);
        ri->setBrush(b);
        break;
    case 2:
        b.setStyle(Qt::Dense7Pattern);
        ri->setBrush(b);
        break;
    case 3:
        b.setStyle(Qt::CrossPattern);
        ri->setBrush(b);
        break;
    case 4:
        QLinearGradient gradient(QPointF(0,25),QPointF(100,75));
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, userColor);
        ri->setBrush(gradient);
        break;
    }
}
