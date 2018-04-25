#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H


#include <QGraphicsView>
#include <QGLWidget>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QObject>

class GraphicsView : public QGraphicsView
{
Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene,QWidget *parent = NULL);
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        fitInView(scene()->sceneRect());
        QGraphicsView::resizeEvent(event);
    }
};

#endif // GRAPHICSVIEW_H
