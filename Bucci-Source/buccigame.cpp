#include "buccigame.h"

#include <QPainter>
#include <cstdlib>
#include <ctime>

#include <QDebug>
#include <QMouseEvent>

BucciGame::BucciGame(QWidget *parent) : QWidget(parent)
{
    deck = new Deck();
    player = new Player();
    pickup = new QPushButton("Pick Up Pile", this);
    layout = new QVBoxLayout();

    layout->addWidget(pickup);

    setLayout(layout);

    turn = 0;

    drawStack = QRect(this->width() / 2 + 30, this->height() / 2 - 20, 30, 40);
    discardPile = QRect(this->width() / 2 - 10, this->height() / 2 - 20, 30, 40);
    deadPile = QRect(this->width() / 2 - 50, this->height() / 2 - 20, 30, 40);
    cardBack = new QPixmap("../Bucci-Source/Images/card_back.png");

    timer = new QTimer();
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateField()));
    timer->start();

    connect(pickup, SIGNAL(clicked()), this, SLOT(pickupCards()));

    //initializes the deck
    deck->init();
    setVecs();

    mousePos = new QPoint(0, 0);
    showInvalidMove = false;



}

void BucciGame::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    paint.setPen(Qt::black);

    paint.drawRect(drawStack);

    paint.drawRect(discardPile);

    paint.drawRect(deadPile);



    if(showInvalidMove)
    {
        paint.drawText(discardPile.x() - 10, discardPile.y() + 70, QString("Invalid Move"));
    }

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(0 == i && !player->isFaceDownEmpty()) //face downs
            {
                (*(player->getFaceDownAt(j))).drawCard(paint, i, (*(player->getFaceDownAt(j))).getCardValue());
            }
            else if(1 == i && !player->isFaceUpEmpty()) //face ups
            {
                (*(player->getFaceUpAt(j))).drawCard(paint, i, (*(player->getFaceUpAt(j))).getCardValue());
            }
            else if(2 == i && !player->isHandEmpty()) //hand
            {
//                (*(player->getCardAt(j))).drawCard(paint, i, (*(player->getCardAt(j))).getCardValue());
                foreach(Card *card, player->hand)
                {
                    card->drawCard(paint, i, card->getCardValue());
                }
            }
        }
    }

    for(int i = 0; i < 3; i++)
    {
        if(0 == i)  //draw pile
        {
            (*(shuffledDeck.at(0))).drawCard(paint, i, drawStack, (*(shuffledDeck.at(0))).getCardValue());
        }
        else if(1 == i) //discard pile
        {
            if(discardStack.at(discardStack.size() - 1)->getCardValue().indexOf("0") != 0)
            {
                (*(discardStack.at(discardStack.size() - 1))).drawCard(paint, i, discardPile, (*(discardStack.at(discardStack.size() - 1))).getCardValue());
            }
            else
            {
                paint.drawRect(discardPile);
            }
        }
        else if(2 == i) //dead pile
        {
            if(!deadStack.empty())
            {
                paint.drawPixmap(deadPile, *cardBack);
            }
            else
            {
                paint.drawRect(deadPile);
            }
        }
    }

    //=================
    //
    //Developer stuff
    //
    //=================

    QPainter devPaint(this);
    devPaint.setPen(Qt::red);
    devPaint.drawText(10, 20, QString("Player face downs: %1, %2, %3").arg((*(player->getFaceDownAt(0))).getCardValue(), (*(player->getFaceDownAt(1))).getCardValue(), (*(player->getFaceDownAt(2))).getCardValue()));
    devPaint.drawText(10, 30, QString("Player face ups: %1, %2, %3").arg((*(player->getFaceUpAt(0))).getCardValue(), (*(player->getFaceUpAt(1))).getCardValue(), (*(player->getFaceUpAt(2))).getCardValue()));
    devPaint.drawText(10, 40, QString("Player hand: %1, %2, %3").arg((*(player->getCardAt(0))).getCardValue(), (*(player->getCardAt(1))).getCardValue(), (*(player->getCardAt(2))).getCardValue()));
    devPaint.drawText(10, 50, QString("Discard: %1").arg((*(discardStack.at(discardStack.size() - 1))).getCardValue()));
    devPaint.drawText(10, 70, QString("Turn: %1").arg(turn));

    if(!deadStack.empty())
    {
        devPaint.drawText(10, 60, QString("Dead: %1").arg((*(deadStack.at(deadStack.size() - 1))).getCardValue()));
    }
}

void BucciGame::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(player->getNumOfCardsInHand() != 0)
        {
            qDebug() << "Cards in hand:" << player->getNumOfCardsInHand();

            for(int i = 0; i < player->getNumOfCardsInHand(); i++)
            {
                if((*(player->getCardAt(i))).containsPoint(e->localPos().x(), e->localPos().y(), QRect((*(player->getCardAt(i))).getPosX(), (*(player->getCardAt(i))).getPosY(), (*(player->getCardAt(i))).getSizeX(), (*(player->getCardAt(i))).getSizeY())))
                {
                    qDebug() << "Clicked in card" << i << "," << (*(player->getCardAt(i))).getCardValue() << "Compare Value:" << player->getCardAt(i)->getCompareValue();

                    if(discardStack.at(discardStack.size() -1)->getCompareValue() <= player->getCardAt(i)->getCompareValue())
                    {
                        if(showInvalidMove)
                            showInvalidMove = false;

                        discardStack.push_back(player->getCardAt(i));

                        if(player->getNumOfCardsInHand() > 2)
                        {
                            goto newTurn;
                        }
                    }
                    else if(player->getCardAt(i)->getCompareValue() == 2 || player->getCardAt(i)->getCompareValue() == 10 || player->getCardAt(i)->getCompareValue() == 1)
                    {
                        if(showInvalidMove)
                            showInvalidMove = false;

                        discardStack.push_back(player->getCardAt(i));

                        if((*(discardStack.at(discardStack.size() - 1))).getCompareValue() == 10)
                        {
                            qDebug() << "Killing Discard";

                            foreach(Card* card, discardStack)
                            {
                                deadStack.push_back(card);
                            }

                            discardStack.remove(0, discardStack.size() - 1);

                            foreach(Card* card, discardStack)
                            {
                                qDebug() << card->getCardValue();
                            }
                        }

                        discardStack.at(discardStack.size() - 1)->setCompareValue(2);
                    }
                    else
                    {
                        showInvalidMove = true;
                        goto newTurn;
                    }

                    player->replaceCard(i, shuffledDeck.at(0));
                    player->setCardCoordAt(2, i, this);
                    shuffledDeck.erase(shuffledDeck.begin());
newTurn:
                    turn++;

                    break;
                }

            }
        }
        else if(0 == player->getNumOfCardsInHand() && shuffledDeck.empty())
        {
            for(int i = 0; i < 3; i++)
            {
                if((*(player->getFaceUpAt(i))).containsPoint(e->x(), e->y(), QRect(player->getFaceUpAt(i)->getPosX(), player->getFaceUpAt(i)->getPosY(), player->getFaceUpAt(i)->getSizeX(), player->getFaceUpAt(i)->getSizeY())))
                {
                    qDebug() << "Clicked in card" << i << "," << (*(player->getFaceUpAt(i))).getCardValue();

                    turn++;

                    if((*(discardStack.at(discardStack.size() - 1))).getCardValue().indexOf("0") == 0)
                    {
                        qDebug() << "Killing Discard";

                        foreach(Card* card, discardStack)
                        {
                            deadStack.push_back(card);
                        }

                        discardStack.remove(0, discardStack.size() - 1);

                        foreach(Card* card, discardStack)
                        {
                            qDebug() << card->getCardValue();
                        }
                    }

                    break;
                }
            }
        }
        else if(0 == player->getNumOfCardsInHand() && shuffledDeck.empty() && 0 == player->getNumOfFaceUps())
        {
            for(int i = 0; i < 3; i++)
            {
                if((*(player->getFaceDownAt(i))).containsPoint(e->x(), e->y(), QRect(player->getFaceDownAt(i)->getPosX(), player->getFaceDownAt(i)->getPosY(), player->getFaceDownAt(i)->getSizeX(), player->getFaceDownAt(i)->getSizeY())))
                {
                    qDebug() << "Clicked in card" << i << "," << (*(player->getFaceDownAt(i))).getCardValue();

                    turn++;

                    if((*(discardStack.at(discardStack.size() - 1))).getCardValue().indexOf("0") == 0)
                    {
                        qDebug() << "Killing Discard";

                        foreach(Card* card, discardStack)
                        {
                            deadStack.push_back(card);
                        }

                        discardStack.remove(0, discardStack.size() - 1);

                        foreach(Card* card, discardStack)
                        {
                            qDebug() << card->getCardValue();
                        }
                    }
                    break;
                }
            }

        }
    }
}


BucciGame::~BucciGame()
{
    qDebug() << "Deconstructor called";
    delete timer;
    delete player;

    if(!shuffledDeck.empty())
    {
        shuffledDeck.clear();
    }

    if(!discardStack.empty())
    {
        discardStack.clear();
    }

    if(!deckRef.empty())
    {
        deckRef.clear();
    }

    if(!deadStack.empty())
    {
        deadStack.clear();
    }
}

void BucciGame::setVecs()
{
    //Puts the deck into a vector for game setup

    qDebug() << "Setting up Deck vector";

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            Card *card = new Card();
            card->setCardValue(deck->getCardAt(i, j));
            card->initCompareValue(card);
            deckRef.push_back(card);
            qDebug() << (*(deckRef.at(deckRef.size() - 1))).getCardValue();
        }
    }

    qDebug() << "Done";

    //=============
    //Shuffle Cards
    //=============

    qDebug() << "Shuffling cards";

    srand(time(0));

    double randDbl;
    int index;

    for(int i = 0; i < 52; i++)
    {
newRand:
        randDbl = (rand() / static_cast<double>(RAND_MAX)) * deckRef.size();
        index = randDbl;

        if(!shuffledDeck.empty())
        {
            if(!this->contains(deckRef.at(index), shuffledDeck))
            {
                shuffledDeck.push_back(deckRef.at(index));
                qDebug() <<"Card at Index " << i << (*(deckRef.at(index))).getCardValue();
            }
            else
            {
                goto newRand;
            }
        }
        else
        {
            shuffledDeck.push_back(deckRef.at(index));
            qDebug() <<"Card at Index " << i << (*(deckRef.at(index))).getCardValue();
        }
    }

    qDebug() << "Done";

    //===========
    //Deal Cards
    //===========

    qDebug() << "Dealing cards";

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j ++)
        {
            if(0 == i)
            {
                player->setFaceDown(shuffledDeck.at(0));

                if(0 == j)
                {
                    (*(player->getFaceDownAt(j))).setX(this->width() / 2 - 55);
                }
                else if(1 == j || 2 == j)
                {
                    (*(player->getFaceDownAt(j))).setX((*(player->getFaceDownAt(j - 1))).getPosX() + 45);
                }

                (*(player->getFaceDownAt(j))).setY(this->height() - (this->height() / 3));

                shuffledDeck.erase(shuffledDeck.begin());
            }
            else if(1 == i)
            {
                player->setFaceUp(shuffledDeck.at(0));

                if(0 == j)
                {
                    (*(player->getFaceUpAt(j))).setX(this->width() / 2 - 55);
                }
                else if(1 == j || 2 == j)
                {
                    (*(player->getFaceUpAt(j))).setX((*(player->getFaceUpAt(j - 1))).getPosX() + 45);
                }

                (*(player->getFaceUpAt(j))).setY(this->height() - (this->height() / 3) + 15);

                shuffledDeck.erase(shuffledDeck.begin());

            }
            else if(2 == i)
            {
                player->setHand(shuffledDeck.at(0));

                if(0 == j)
                {
                    (*(player->getCardAt(j))).setX(this->width() / 2 - 55);
                }
                else if(1 == j || 2 == j)
                {
                    (*(player->getCardAt(j))).setX((*(player->getCardAt(j - 1))).getPosX() + 45);
                }

                (*(player->getCardAt(j))).setY(this->height() - (this->height() / 3) + 65);

                shuffledDeck.erase(shuffledDeck.begin());
            }
        }
    }

    //===================
    //Sets the first card
    //===================
    discardStack.push_back(shuffledDeck.at(0));

    shuffledDeck.erase(shuffledDeck.begin());

    qDebug() << "Discard stack:" << (*(discardStack.at(0))).getCardValue();

    qDebug() << "Done";
}

bool BucciGame::contains(Card* card, vector<Card*> deck)
{
    bool inDeck = false;

    for(unsigned int i = 0; i < deck.size(); i++)
    {
        if((*(deck.at(i))).getCardValue() == card->getCardValue())
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

void BucciGame::updateField()
{
    player->setNumOfCardsInHand();

    this->update();
}

void BucciGame::pickupCards()
{
    foreach(Card *card, discardStack)
    {
        player->setHand(card);
    }

    discardStack.remove(0, discardStack.size() - 1);
}


