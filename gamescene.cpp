#include "gamescene.h"
#include <QGraphicsEllipseItem>

GameScene::GameScene(Paddle *p, Ball *b, int x, int y, int width, int height) : QGraphicsScene(x,y,width,height),
    paddle(p), ball(b), initWidth(width), initHeight(height)
{
    this->setBackgroundBrush(QBrush(QColor(42, 64, 96)));
}

void GameScene::clearScene()
{
    removeItem(ball);
    removeItem(paddle);
    clear();
}

//pseudo-random scene generation
void GameScene::initScene()
{
    qreal brickHeight = (initHeight * 0.35)/9;
    qreal brickWidth = (qreal)initWidth / 20;
    qreal currX = 0;
    qreal currY = initHeight * 0.1;//begin of first row
    Brick* newBric;
    currentBricksNumber = 0;
    for(auto i=0; i<9; ++i)
    {
        int bricksInRow = (QRandomGenerator::system()->generate() % 13) + 8;
        currentBricksNumber += bricksInRow;
        qreal spacing = (initWidth - bricksInRow * brickWidth)/2;
        currX = spacing;
        QColor brickColor = QColor::fromRgb(QRandomGenerator::system()->generate());
        while(brickColor.red() == 255 && brickColor.green() == 255 && brickColor.blue() == 255)
        {
            brickColor = QColor::fromRgb(QRandomGenerator::system()->generate());
        }
        if((bricksInRow % 2 == 1) || ((QRandomGenerator::system()->generate() % 20) > 10))
        {
            for(auto j=0; j<bricksInRow; ++j)
            {
                newBric = new Brick(0,0,brickWidth,brickHeight,brickColor);
                addItem(newBric);
                newBric->setPos(currX,currY);
                currX += brickWidth;
            }
        }
        else
        {
            currX = 0;
            qreal rightX = initWidth - brickWidth;
            for(auto k=0; k<(bricksInRow/2); ++k)
            {
                newBric = new Brick(0,0,brickWidth,brickHeight,brickColor);
                addItem(newBric);
                newBric->setPos(currX,currY);

                newBric = new Brick(0,0,brickWidth,brickHeight,brickColor);
                addItem(newBric);
                newBric->setPos(rightX,currY);

                currX += brickWidth;
                rightX -= brickWidth;
            }
        }
        currY += brickHeight;
    }
    initPaddle();
    initBall();
    emit sceneInitialized();
}

void GameScene::initPaddle()
{
    addItem(paddle);
    paddleHLevel = initHeight-paddle->getHeight();
    paddle->setPosition(QPointF((initWidth-paddle->getWidth())/2,paddleHLevel));
}

void GameScene::initBall()
{
   addItem(ball);
   ball->setPosition(QPointF(width()/2,height()/2));
}

void GameScene::setBallInitPos()
{
    ball->setPosition(QPointF(width()/2,height() - 2*ball->getRadius()));
}

void GameScene::destroyBrick(Brick *b)
{
    removeItem(b);
    delete b;
    currentBricksNumber -= 1;
    if(currentBricksNumber == 0)
    {
        emit allBricksDestroyed();
    }
}
