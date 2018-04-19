#include "gamemainwindow.h"
#include "ui_gamemainwindow.h"
#include "paddlepicker.h"

GameMainWindow::GameMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameMainWindow)
{
    ui->setupUi(this);
    first = ui->centralWidget;
    QGraphicsScene *pickerScene = new QGraphicsScene(0,0,100,100);
    pp = new PaddlePicker(pickerScene,this);
    ui->verticalLayout->insertWidget(2,pp);
    connect(this,SIGNAL(colorChanged(QColor)),pp,SLOT(updateColor(QColor)));
    connect(this,SIGNAL(brushChanged(int)),pp,SLOT(setBrush(int)));
}

GameMainWindow::~GameMainWindow()
{
    delete ui;
}

void GameMainWindow::on_playButton_clicked()
{
    Paddle *p = new Paddle();
    Ball *b = new Ball();
    GameScene *g = new GameScene(p,b,0,0,ui->centralWidget->width(),ui->centralWidget->height());
    g->initScene();
    gv = new GraphicsView(g,this);
    gc = new GameController(g,this);
    this->setCentralWidget(gv);
}

void GameMainWindow::on_rBox_valueChanged(int arg1)
{
    emit colorChanged(QColor(arg1,ui->gBox->value(),ui->bBox->value()));
}

void GameMainWindow::on_gBox_valueChanged(int arg1)
{
    emit colorChanged(QColor(ui->rBox->value(),arg1,ui->bBox->value()));
}

void GameMainWindow::on_bBox_valueChanged(int arg1)
{
    emit colorChanged(QColor(ui->rBox->value(),ui->gBox->value(),arg1));
}

void GameMainWindow::on_horizontalSlider_valueChanged(int value)
{
    emit brushChanged(value);
}
