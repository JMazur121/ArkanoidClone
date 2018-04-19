#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGLWidget>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = NULL);
protected:
    void resizeEvent(QResizeEvent *event) override
    {
        fitInView(scene()->sceneRect());
        QGraphicsView::resizeEvent(event);
    }
};

#endif // GRAPHICSVIEW_H
