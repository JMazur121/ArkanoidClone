#include "gamescene.h"

GameScene::GameScene(Paddle *p, Ball *b, int x, int y, int width, int height) : QGraphicsScene(x,y,width,height),
    paddle(p), ball(b), initWidth(width), initHeight(height)
{
    this->setBackgroundBrush(QBrush(QColor(42, 64, 96)));
    randomGenerator = QRandomGenerator::system();
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
    qreal brickWidth = initWidth / 20;
    qreal currX = 0;
    qreal currY = initHeight * 0.1;//begin of first row
    Brick* newBric;
    for(auto i=0; i<9; ++i) {
        int bricksInRow = (randomGenerator->generate() % 13) + 8;
        qreal spacing = (initWidth - bricksInRow * brickWidth)/2;
        currX = spacing;
        QColor brickColor = QColor::fromRgb(randomGenerator->generate());
        while (brickColor.red() == 255 && brickColor.green() == 255 && brickColor.blue() == 255) {
            brickColor = QColor::fromRgb(randomGenerator->generate());
        }
        for(auto j=0; j<bricksInRow; ++j) {
            newBric = new Brick(currX,currY,brickWidth,brickHeight,brickColor);
            addItem(newBric);
            currX += brickWidth;
        }
        currY += brickHeight;
    }
}
