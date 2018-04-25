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
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(newBrush(int)));
    connect(ui->rBox,SIGNAL(valueChanged(int)),this,SLOT(colorFromRGB()));
    connect(ui->gBox,SIGNAL(valueChanged(int)),this,SLOT(colorFromRGB()));
    connect(ui->bBox,SIGNAL(valueChanged(int)),this,SLOT(colorFromRGB()));
    connect(ui->playButton,SIGNAL(pressed()),this,SLOT(startGame()));
}

GameMainWindow::~GameMainWindow()
{
    delete ui;
}

void GameMainWindow::startGame()
{
    Paddle *p = new Paddle(0,0,ui->centralWidget->width() * 0.20,ui->centralWidget->height()* 0.03,pp->getSelectedBrush());
    qreal radius = ((qreal)ui->centralWidget->width())/40;
    Ball *b = new Ball(radius);
    GameScene *g = new GameScene(p,b,0,0,ui->centralWidget->width(),ui->centralWidget->height());
    gv = new GraphicsView(g,this);
    gc = new GameController(g,this);
    connect(g,SIGNAL(sceneInitialized()),gc,SLOT(gameInitialized()));
    connect(gc,SIGNAL(paddleStateChanged(Paddle::paddleMovement)),p,SLOT(setMovement(Paddle::paddleMovement)));
    g->initScene();
    this->setCentralWidget(gv);
    g->installEventFilter(gc);
}

void GameMainWindow::colorFromRGB()
{
    emit colorChanged(QColor(ui->rBox->value(),ui->gBox->value(),ui->bBox->value()));
}

void GameMainWindow::newBrush(int value)
{
    emit brushChanged(value);
}

void GameMainWindow::on_helpButton_clicked()
{
    QString info = "Zacznij od skonfigurowania swojej paletki. Używając trzech wskaźników oznaczonych literami "
                   "RGB możesz wybrać dodatkowy kolor swojej paletki. Poziomy suwak pozwala na wybranie jednego z "
                   "dostępnych deseni.\n Aby rozpocząć grę kliknij przycisk Rozpocznij grę. Zostanie wyświetlone okno gry.\n"
                   "Aby rozpocząć poziom, wciśnij SPACJĘ. Do poruszania paletką użyj klawiszy LEWY i PRAWY. Jeśli chcesz "
                   "zatrzymać grę, wciśnij P.\nNa każdym poziomie posiadasz 3 szanse. Po utracie szans, lub zniszczeniu "
                   "wszystkich bloczków, możesz grać dalej. Wciśnij SPACJĘ aby wygenerować kolejny poziom.";
    QMessageBox::information(this,"Jak zagrać",info);
}
