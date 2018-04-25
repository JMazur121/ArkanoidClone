#include "gamecontroller.h"

GameController::GameController(GameScene *g, QObject *parent) : QObject(parent), gs(g)
{
    installPaddleAnimation();
    qreal sceneW = gs->width();
    qreal sceneH = gs->height();
    sceneDiag = sqrt((sceneW*sceneW)+(sceneH*sceneH));
    installBallAnimation();
    ball = gs->getBall();
    ballRadius = ball->getRadius();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(gs,SIGNAL(allBricksDestroyed()),this,SLOT(levelWon()));
}

bool GameController::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease)
        return false;
    else
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(event->type() == QEvent::KeyPress)
            return keyPressHandler(keyEvent);
        else
            return keyReleaseHandler(keyEvent);
    }
}

void GameController::gameInitialized()
{
    gState = Game_Initialized;
    keyPressed = false;
    lives = 3;
    resume = false;
}

void GameController::paddleAnimFinished()
{
    emit paddleStateChanged(Paddle::None);
}

void GameController::update()
{
    //rigth wall
    if((gs->width() - ball->x()) <= ballRadius)
    {
        ballMovement->stop();
        revertBallXVelocity();
        moveBall();
        return;
    }//left wall
    else if(ball->x() <= ballRadius)
    {
        ballMovement->stop();
        revertBallXVelocity();
        moveBall();
        return;
    }//upper wall
    else if(ball->y() <= ballRadius)
    {
        ballMovement->stop();
        revertBallYVelocity();
        moveBall();
        return;
    }//down wall
    else if((gs->height() - ball->y()) <= ballRadius)
    {
        chanceLost();
        return;
    }

    QList<QGraphicsItem*> collidingItems = gs->collidingItems(ball);

    if(!collidingItems.isEmpty())
    {
        bool brickFirstY = true;
        bool brickFirstX = true;
        ballMovement->stop();
        foreach (QGraphicsItem *i, collidingItems) {
            if(i->data(0) == GamePaddle)
            {
                Paddle *p = static_cast<Paddle *>(i);
                if((ball->x() > p->x() || ball->x() < p->x()) && (ball->y() > p->y()))
                {
                    revertBallXVelocity();
                    //moveBall();
                    //return;
                }
                else
                {
                    revertBallYVelocity();
                    //moveBall();
                    //return;
                }
            }
            else if(i->data(0) == GameBlock)
            {
                Brick* b = static_cast<Brick*>(i);
                if(ball->y() >= b->boundingRect().bottom())
                {
                    if(brickFirstY)
                        revertBallYVelocity();
                    brickFirstY = false;
                }
                else if(ball->y() <= b->boundingRect().top())
                {
                    if(brickFirstY)
                        revertBallYVelocity();
                    brickFirstY = false;
                }
                else if(ball->x() < b->boundingRect().left())
                {
                    if(brickFirstX)
                        revertBallXVelocity();
                    brickFirstX = false;
                }
                else if(ball->x() > b->boundingRect().right())
                {
                    if(brickFirstX)
                        revertBallXVelocity();
                    brickFirstX = false;
                }

                gs->destroyBrick(b);
            }
        }
        moveBall();
        return;
    }

}

void GameController::levelWon()
{
    timer->stop();
    ballMovement->stop();
    keyPressed = false;
    if(paddleMovement->state() == paddleMovement->Running)
    {
        paddleMovement->stop();
        emit paddleStateChanged(Paddle::None);
    }
    gState = Game_Won;
}

void GameController::pauseAnimations()
{
    timer->stop();
    if(paddleMovement->state() == paddleMovement->Running)
        paddleMovement->pause();
    if(ballMovement->state() == ballMovement->Running)
        ballMovement->pause();
    gState = Game_Paused;
}

void GameController::resumeAnimations()
{
    timer->start(timerPeriod);
    if(paddleMovement->state() == paddleMovement->Paused)
        paddleMovement->resume();
    if(ballMovement->state() == ballMovement->Paused)
        ballMovement->resume();
    gState = Game_Ongoing;
}

void GameController::installPaddleAnimation()
{
    paddleMovement = new QPropertyAnimation(gs->getPadlle(),"paddlePos");
    connect(paddleMovement,SIGNAL(finished()),this,SLOT(paddleAnimFinished()));
    paddleSpeed = (qreal)(gs->getInitWidth())/1200;    //v = s/t, t=[ms]
}

void GameController::installBallAnimation()
{
    ballMovement = new QPropertyAnimation(gs->getBall(),"ballPos");
    countBallTranslation();
}

void GameController::movePaddleLeft()
{
    paddleMovement->setEndValue(QPointF(0,gs->getPaddleHLevel()));
    paddleMovement->setDuration(gs->getPadlle()->x()/paddleSpeed);
    paddleMovement->start();
}

void GameController::movePaddleRight()
{
    paddleMovement->setEndValue(QPointF(gs->width() - gs->getPadlle()->getWidth(),gs->getPaddleHLevel()));
    paddleMovement->setDuration((gs->width() - gs->getPadlle()->getWidth() - gs->getPadlle()->x())/paddleSpeed);
    paddleMovement->start();
}

void GameController::moveBall()
{
    ballMovement->setEndValue(ballEndPoint());
    ballMovement->setDuration(time);
    ballMovement->start();
}

bool GameController::keyPressHandler(QKeyEvent *keyEvent)
{
    if(gState == Game_Ongoing)
    {
        if(keyEvent->key() == Qt::Key_P)
        {
            pauseAnimations();
            return true;
        }
        else if(keyEvent->key() == Qt::Key_Left && gs->getPadlle()->getMovement() == Paddle::None && !keyPressed)
        {
            movePaddleLeft();
            keyPressed = true;
            emit paddleStateChanged(Paddle::Left);
            return true;
        }
        else if(keyEvent->key() == Qt::Key_Left && gs->getPadlle()->getMovement() == Paddle::Left && keyPressed)
            return false;
        else if(keyEvent->key() == Qt::Key_Right && gs->getPadlle()->getMovement() == Paddle::None && !keyPressed)
        {
            movePaddleRight();
            keyPressed = true;
            emit paddleStateChanged(Paddle::Right);
            return true;
        }
        else
            return false;
    }
    else if(keyEvent->key() == Qt::Key_Space && gState == Game_Won)
    {
        newLevel();
        return true;
    }
    else if(keyEvent->key() == Qt::Key_Space && gState == Game_Lost)
    {
        newLevel();
        return true;
    }
    else if(keyEvent->key() == Qt::Key_Space && gState == Game_Chance_Lost)
    {
        resumeAfterChanceLost();
        return true;
    }
    else if(gState == Game_Paused && keyEvent->key() == Qt::Key_P)
    {
        resumeAnimations();
        return true;
    }
    else if(gState == Game_Initialized && keyEvent->key() == Qt::Key_Space)
    {
        gameStart();
        return true;
    }
    return false;
}

bool GameController::keyReleaseHandler(QKeyEvent *keyEvent)
{
    if(keyEvent->key() != Qt::Key_Left && keyEvent->key() != Qt::Key_Right)
        return false;
    if(paddleMovement->state() == paddleMovement->Running)
        paddleMovement->stop();
    keyPressed = false;
    emit paddleStateChanged(Paddle::None);
    return true;
}

void GameController::gameStart()
{
    gState = Game_Ongoing;
    moveBall();
    timer->start(timerPeriod);
    emit paddleStateChanged(Paddle::None);
}

QPointF GameController::ballEndPoint()
{
    QPointF ballPos = gs->getBall()->pos();
    return (ballPos + translation);
}

void GameController::countBallTranslation()
{
    QPointF speed(0,0);
    qreal bspeed = 0.8*paddleSpeed;
    qreal tmp,tmp2;
    while ((tmp = QRandomGenerator::system()->bounded(bspeed)) < 0.3) {
    }
    tmp2 = sqrt((bspeed*bspeed)-(tmp*tmp));
    if(tmp > tmp2)
    {
        speed.setX(tmp2);
        speed.setY(tmp);
    }
    else
    {
        speed.setX(tmp);
        speed.setY(tmp2);
    }
    ballSpeed = speed;
    bspeedLength = sqrt((ballSpeed.x() * ballSpeed.x())+(ballSpeed.y() * ballSpeed.y()));//długosc wektora predkosci
    tmp2 = sceneDiag/bspeedLength;
    translation = ballSpeed * tmp2;
    time = (int)tmp2;
}

void GameController::revertBallYVelocity()
{
    //ballSpeed.setY(ballSpeed.y() * -1);
    translation.setY(translation.y() * -1);
}

void GameController::revertBallXVelocity()
{
    //ballSpeed.setX(ballSpeed.x() * -1);
    translation.setX(translation.x() * -1);
}

void GameController::chanceLost()
{
    timer->stop();
    ballMovement->stop();
    keyPressed = false;
    if(paddleMovement->state() == paddleMovement->Running)
    {
        paddleMovement->stop();
        emit paddleStateChanged(Paddle::None);
    }
    lives -= 1;
    gState = (lives == 0) ? Game_Lost : Game_Chance_Lost;
    resume = true;
}

void GameController::resumeAfterChanceLost()
{
    if(resume)
    {
        gs->setBallInitPos();
        resume = false;
        return;
    }
    translation.setY(-translation.y());
    emit paddleStateChanged(Paddle::None);
    gState = Game_Ongoing;
    moveBall();
    timer->start(timerPeriod);
}

void GameController::newLevel()
{
    gs->clearScene();
    countBallTranslation();
    gs->initScene();
}
