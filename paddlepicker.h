#ifndef PADDLEPICKER_H
#define PADDLEPICKER_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

class PaddlePicker : public QGraphicsView
{
public:
    PaddlePicker(QGraphicsScene *scene, QWidget *parent = NULL);

    QColor getColor() const;
    void updateColor(QColor newColor);
    void setBrush(int val);
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        fitInView(scene()->sceneRect());
        QGraphicsView::resizeEvent(event);
    }
private:
    QColor userColor;
    void updatePaddle();
    QGraphicsRectItem* ri;
    QGraphicsScene *s;
    enum styles {
        Checkers = 0,
        SolidPattern = 1,
        Dense7Pattern = 2,
        CrossPattern = 3,
        LinearGradient = 4

    };
    int style = 0;
};

#endif // PADDLEPICKER_H
