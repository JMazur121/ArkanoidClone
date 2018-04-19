#ifndef PADDLEPICKER_H
#define PADDLEPICKER_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QRectF>

class PaddleRect : public QGraphicsRectItem
{
public:
    PaddleRect(int style) : QGraphicsRectItem(0,25,100,50), paddleStyle(style) {
        topChecker = QRectF(QPointF(0,25),QSizeF(10,25));
        bottomChecker = QRectF(QPointF(0,50),QSizeF(10,25));
        secondColor = QColor(100,100,100);
    }
    void setStyle(int style) {this->paddleStyle = style;}
    void setColor(QColor color) {this->secondColor = color;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *) override
    {
        QPainterPath path;
        path.addRect(rect());
        painter->setPen(pen());
        if(paddleStyle){
            painter->fillPath(path,this->brush());
            painter->drawPath(path);
        }
        else{
            for(auto i=0; i<5; ++i){
                painter->fillRect(topChecker,Qt::white);
                painter->fillRect(bottomChecker,secondColor);
                topChecker.moveLeft(topChecker.x()+10);
                bottomChecker.moveLeft(bottomChecker.x()+10);
                painter->fillRect(topChecker,secondColor);
                painter->fillRect(bottomChecker,Qt::white);
                topChecker.moveLeft(topChecker.x()+10);
                bottomChecker.moveLeft(bottomChecker.x()+10);
            }
            painter->drawPath(path);
            topChecker.setTopLeft(QPointF(0,25));
            bottomChecker.setTopLeft(QPointF(0,50));
        }
    }
private:
    int paddleStyle;
    QRectF topChecker;
    QRectF bottomChecker;
    QColor secondColor;
};

class PaddlePicker : public QGraphicsView
{
Q_OBJECT
public:
    PaddlePicker(QGraphicsScene *scene, QWidget *parent = NULL);
    QColor getColor() const;
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
    PaddleRect* ri;
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
