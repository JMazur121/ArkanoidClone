#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QMainWindow>
#include "graphicsview.h"
#include "gamecontroller.h"
#include "paddlepicker.h"

namespace Ui {
class GameMainWindow;
}

class GameMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameMainWindow(QWidget *parent = 0);
    ~GameMainWindow();

private slots:
    void on_playButton_clicked();
    void on_rBox_valueChanged(int arg1);
    void on_gBox_valueChanged(int arg1);
    void on_bBox_valueChanged(int arg1);
    void on_horizontalSlider_valueChanged(int value);

signals:
    void colorChanged(QColor newColor);
    void brushChanged(int newBrush);
private:
    Ui::GameMainWindow *ui;
    QWidget *first;
    GraphicsView *gv;
    GameController *gc;
    PaddlePicker *pp;
};

#endif // GAMEMAINWINDOW_H
