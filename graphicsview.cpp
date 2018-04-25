#include "graphicsview.h"

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent)
{
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QGLFormat glFormat(QGL::SampleBuffers);
    //glFormat.setSwapInterval(1);
    this->setViewport(new QGLWidget(glFormat,this));
}
