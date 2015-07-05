#include "buccigame.h"

#include <QPainter>
#include <cstdlib>
#include <ctime>

#include <QDebug>

BucciGame::BucciGame(QWidget *parent) : QWidget(parent)
{
    card = new Card();

    turn = 0;

    drawStack = QRect(this->width() / 2 + 30, this->height() / 2 - 20, 30, 40);
    discardPile = QRect(this->width() / 2 - 10, this->height() / 2 - 20, 30, 40);
    deadPile = QRect(this->width() / 2 - 50, this->height() / 2 - 20, 30, 40);

    timer = new QTimer();
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start();

    //initializes the deck
    card->init();
    setVecs();

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
    //Puts the deck into a vector for game setup
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            Card* card1 = new Card();
            card1->setCardValue(card->getCardAt(i, j));
            deck.push_back(*card1);
            delete card1;
        }
    }

    //=============
    //Shuffle Cards
    //=============

    srand(time(0));

    double randDbl;
    int index;

    for(int i = 0; i < 52; i++)
    {
newRand:
        randDbl = (rand() / static_cast<double>(RAND_MAX)) * deck.size();
        index = randDbl;

        if(shuffledDeck.size() != 0)
        {
            if(!this->contains(deck.at(index), shuffledDeck))
            {
                shuffledDeck.push_back(deck.at(index));
            }
            else
            {
                qDebug() << "Card is already in shuffled deck. Finding new card.";
                goto newRand;
            }
        }
        else
        {
            shuffledDeck.push_back(deck.at(index));
        }

        qDebug() << "ShuffledDeck size: " << shuffledDeck.size();
        qDebug() << "Card: " << (deck.at(index)).getCardValue();
    }

    //===========
    //Deal Cards
    //===========



}

bool BucciGame::contains(Card card, vector<Card> &deck)
{
    bool inDeck = false;

    for(int i = 0; i < deck.size(); i++)
    {
        if((deck.at(i)).getCardValue() == card.getCardValue())
        {
            inDeck = true;
            break;
        }
        else
        {
            inDeck = false;
        }
    }

    return inDeck;

}


