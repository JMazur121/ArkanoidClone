#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "gamescene.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(GameScene *g, QObject *parent = nullptr);
private:
    GameScene *gs;
signals:

public slots:
};

#endif // GAMECONTROLLER_H
