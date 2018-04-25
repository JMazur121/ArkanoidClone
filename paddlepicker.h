#ifndef PADDLEPICKER_H
#define PADDLEPICKER_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QRectF>
#include <QBrush>

class PaddlePicker : public QGraphicsView
{
Q_OBJECT
public:
    PaddlePicker(QGraphicsScene *scene, QWidget *parent = NULL);
    QColor getColor() const;
    QBrush getSelectedBrush() const;
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        fitInView(scene()->sceneRect());
        QGraphicsView::resizeEvent(event);
    }
public slots:
    void updateColor(QColor newColor);
    void setBrush(int val);
private:
    QColor userColor;
    QGraphicsRectItem* ri;
    QGraphicsScene *s;
    int style = 0;
};

#endif // PADDLEPICKER_H
