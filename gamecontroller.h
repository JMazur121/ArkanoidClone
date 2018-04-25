#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QPropertyAnimation>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QtMath>
#include <QTimer>
#include <QList>

#include "gamescene.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(GameScene *g, QObject *parent = nullptr);

    enum gameState{
        Game_Initialized,
        Game_Ongoing,
        Game_Paused,
        Game_Chance_Lost,
        Game_Won,
        Game_Lost
    };

    bool eventFilter(QObject *watched, QEvent *event);
public slots:
    void gameInitialized();
    void paddleAnimFinished();
    void update();
    void levelWon();
private:
    GameScene *gs;
    gameState gState;
    QPropertyAnimation *paddleMovement;
    QPropertyAnimation *ballMovement;
    qreal paddleSpeed;
    QPointF ballSpeed;
    QPointF translation;
    qreal sceneDiag;
    qreal bspeedLength;
    qreal ballRadius;
    bool keyPressed;
    QTimer* timer;
    Ball* ball;
    int time;
    int lives;
    bool resume;
    const int timerPeriod = 30;

    void pauseAnimations();
    void resumeAnimations();
    void installPaddleAnimation();
    void installBallAnimation();
    void movePaddleLeft();
    void movePaddleRight();
    void moveBall();
    bool keyPressHandler(QKeyEvent *keyEvent);
    bool keyReleaseHandler(QKeyEvent *keyEvent);
    void gameStart();
    QPointF ballEndPoint();
    void countBallTranslation();
    void revertBallYVelocity();
    void revertBallXVelocity();
    void chanceLost();
    void resumeAfterChanceLost();
    void newLevel();
signals:
    void paddleStateChanged(Paddle::paddleMovement);
};

#endif // GAMECONTROLLER_H
