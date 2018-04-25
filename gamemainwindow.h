#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
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
    void startGame();
    void colorFromRGB();
    void newBrush(int value);

    void on_helpButton_clicked();

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
