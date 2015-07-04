#include "buccigame.h"

#include <QPainter>

BucciGame::BucciGame(QWidget *parent) : QWidget(parent)
{
    turn = 0;
    cardsInHand = 3;

    drawStack = QRect(this->width() / 2 + 30, this->height() / 2 - 20, 30, 40);
    discardPile = QRect(this->width() / 2 - 10, this->height() / 2 - 20, 30, 40);
    deadPile = QRect(this->width() / 2 - 50, this->height() / 2 - 20, 30, 40);

    timer = new QTimer();
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start();
    this->setVecs();

}

void BucciGame::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    QBrush brush;
    brush.setColor(Qt::black);
    paint.setBrush(brush);

    paint.drawRect(drawStack);
    paint.drawRect(discardPile);
    paint.drawRect(deadPile);

    paint.fillRect(drawStack, Qt::blue);
    paint.fillRect(discardPile, Qt::gray);
    paint.fillRect(deadPile, Qt::red);

}

BucciGame::~BucciGame()
{

}

void BucciGame::setVecs()
{
    for(int i = 0; i < 3; i++)
    {
        playerFaceDown = new QRect(this->width() / 2 + 30, this->height() / 4 - 20, 30, 40);
        playerCardsFaceDown.push_back(playerFaceDown);
    }
}


