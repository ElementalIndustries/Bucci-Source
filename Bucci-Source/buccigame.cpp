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

    this->resize(580, 580);

    pickup = new QPushButton("Pick Up Pile", this);
    pickup->move(this->width() / 2 - 66, this->height() - 30);
    pickup->resize(132, 25);

    exit = new QPushButton("Exit", this);
    exit->move(10, this->height() - 30);
    exit->resize(80, 25);

    playCards = new QPushButton("[WIP] DO NOT USE", this);
    playCards->move(this->width() - 110, this->height() - 30);
    playCards->resize(100, 25);

    turn = 0;
    fourCount = 1;

    handEmpty = false;
    faceUpEmpty = false;
    faceDownEmpty = false;

    showInvalidMove = false;
    showKillPile = false;
    showChallenge = false;
    showReset = false;
    showFourKind = false;

    drawStack = QRect(this->width() / 2 + 26, this->height() / 2 - 20, 30, 40);
    discardPile = QRect(this->width() / 2 - 20, this->height() / 2 - 20, 30, 40);
    deadPile = QRect(this->width() / 2 - 66, this->height() / 2 - 20, 30, 40);

    cardBack = new QPixmap("../Bucci-Source/Images/card_back.png");

    timer = new QTimer();
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateField()));
    timer->start();

    connect(pickup, SIGNAL(clicked()), this, SLOT(pickupCards()));
    connect(exit, SIGNAL(clicked()), this, SLOT(close()));
//    connect(playCards, SIGNAL(clicked()), this, SLOT(emptyQueue()));

    //initializes the deck
    deck->init();
    setVecs();


}//end c'tor

BucciGame::~BucciGame()
{
    qDebug() << "Game dec'tor called";
    delete timer;
    delete player;
    delete exit;
    delete cardBack;
    delete pickup;
    delete deck;

    if(!shuffledDeck.empty())
    {
        qDebug() << "Deleting shuffled deck";
        for(int i = 0; i < shuffledDeck.size(); i++)
        {

            delete shuffledDeck.at(i);
        }

        shuffledDeck.clear();
    }

    if(!discardStack.empty())
    {
        qDebug() << "Deleting discard stack";
        for(int i = 0; i < discardStack.size(); i++)
        {
            delete discardStack.at(i);
        }

        discardStack.clear();
    }

    if(!deckRef.empty())
    {
        qDebug() << "Deleting deckRef";
        for(int i = 0; i < deckRef.size(); i++)
        {
            delete deckRef.at(i);
        }

        deckRef.clear();
    }

    if(!deadStack.empty())
    {
        qDebug() << "Deleting kill pile";
        for(int i = 0; i < deadStack.size(); i++)
        {
            delete deadStack.at(i);
        }

        deadStack.clear();
    }
}//end of dec'tor

void BucciGame::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    QPen pen(Qt::black);

    paint.setPen(Qt::black);

    paint.drawRect(drawStack);

    paint.drawRect(discardPile);

    paint.drawRect(deadPile);

    if(showInvalidMove) {paint.drawText(discardPile.x() - 10, discardPile.y() + 55, QString("Invalid Move")); }

    if(showKillPile || showFourKind) {paint.drawText(discardPile.x() - 5, discardPile.y() + 60, QString("Pile Killed")); }

    if(showReset) { paint.drawText(discardPile.x() - 5, discardPile.y() + 60, QString("Pile Reset")); }

    if(showChallenge) { paint.drawText(discardPile.x() - 8, discardPile.y() + 60, QString("Challenge!")); }

    if(showFourKind) {paint.drawText(discardPile.x() - 15, discardPile.y() + 71, QString("Four of a Kind")); }

    QPainter queuePaint(this);
    queuePaint.setPen(pen);

    for(int i = 0; i < 3; i++)
    {
        if(0 == i && !faceDownEmpty) //face downs
        {
            foreach(Card *card, player->playerCardsFaceDown)
            {
                card->drawCard(paint, i , card->getCardValue());
            }
        }
        else if(1 == i && !faceUpEmpty) //face ups
        {
            foreach(Card *card, player->playerCardsFaceUp)
            {
                card->drawCard(paint, i, card->getCardValue());
            }
        }
        else if(2 == i && !handEmpty) //hand
        {
            player->setNumOfCardsInHand();

            for(int j = 0; j < player->getNumOfCardsInHand(); j++)
            {
                setCardCoord(2, j);
                if(player->getCardAt(i)->getInQueue())
                {
                    pen.setColor(Qt::green);
                }
                else
                {
                    pen.setColor(Qt::black);
                }

                player->hand.at(j)->drawCard(queuePaint, i, player->hand.at(j)->getCardValue());
            }
        }
    }

    for(int i = 0; i < 3; i++)
    {
        if(0 == i)  //draw pile
        {
            if(!shuffledDeck.empty())
            {
                if(shuffledDeck.at(shuffledDeck.size() - 1)->getCompareValue() == -1)
                {
                    paint.drawRect(drawStack);
                }
                else
                {
                    paint.drawPixmap(drawStack, *cardBack);
                }
            }
            else
            {
                paint.drawRect(drawStack);
            }
        }
        else if(1 == i) //discard pile
        {
            if(!discardStack.empty())
            {
                if(discardStack.at(discardStack.size() - 1)->getCompareValue() == -1)
                {
                    paint.drawRect(discardPile);
                }
                else
                {
                    (*(discardStack.at(discardStack.size() - 1))).drawCard(paint, i, discardPile, (*(discardStack.at(discardStack.size() - 1))).getCardValue());
                }
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

    if(!faceDownEmpty) { devPaint.drawText(10, 20, QString("Player face downs: %1, %2, %3").arg((*(player->getFaceDownAt(0))).getCompareValue()).arg((*(player->getFaceDownAt(1))).getCompareValue()).arg((*(player->getFaceDownAt(2))).getCompareValue())); }

    if(!faceUpEmpty) { devPaint.drawText(10, 30, QString("Player face ups: %1, %2, %3").arg((*(player->getFaceUpAt(0))).getCompareValue()).arg((*(player->getFaceUpAt(1))).getCompareValue()).arg((*(player->getFaceUpAt(2))).getCompareValue())); }

    if(!handEmpty) { devPaint.drawText(10, 40, QString("Player hand: %1, %2, %3").arg((*(player->getCardAt(0))).getCompareValue()).arg((*(player->getCardAt(1))).getCompareValue()).arg((*(player->getCardAt(2))).getCompareValue())); }

    if(!handEmpty) { devPaint.drawText(10, 50, QString("Cards in hand: %1").arg(player->getNumOfCardsInHand())); }

    devPaint.drawText(10, 60, QString("Discard: %1").arg((*(discardStack.at(discardStack.size() - 1))).getCompareValue()));

    if(!deadStack.empty()) { devPaint.drawText(10, 70, QString("Dead: %1").arg((*(deadStack.at(deadStack.size() - 1))).getCardValue())); }

    devPaint.drawText(10, 80, QString("Turn: %1").arg(turn));
    devPaint.drawText(10, 90, QString("Window Size: %1 x %2").arg(this->width()).arg(this->height()));
    devPaint.drawText(10, 100, QString("Cards Remaining in deck: %1").arg(shuffledDeck.size()));
    devPaint.drawText(10, 110, QString("Four of a Kind count: %1").arg(fourCount));
}//end of paintEvent

void BucciGame::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(handEmpty && faceUpEmpty)
        {
            for(int i = 0; i < 3; i++)
            {
                if((*(player->getFaceDownAt(i))).containsPoint(e->x(), e->y(), QRect(player->getFaceDownAt(i)->getPosX(), player->getFaceDownAt(i)->getPosY(), player->getFaceDownAt(i)->getSizeX(), player->getFaceDownAt(i)->getSizeY())))
                {
                    qDebug() << "Clicked in card" << i << ". Compare Value:" << player->getFaceDownAt(i)->getCompareValue();

                    if(showInvalidMove)
                        showInvalidMove = false;

                    if(showChallenge)
                        showChallenge = false;

                    if(showKillPile)
                        showKillPile = false;

                    if(showReset)
                        showReset = false;

                    if(showFourKind)
                        showFourKind = false;

                    fourCount = 1;

                    for(int j = 0; j < discardStack.size(); j++)
                    {
                        if(player->getFaceDownAt(i)->getCompareValue() == discardStack.at(j)->getCompareValue())
                        {
                            fourCount++;
                        }

                        if(fourCount == 4)
                        {
                            showFourKind = true;
                            break;
                        }
                    }

                    if(player->getFaceDownAt(i)->getCompareValue() == 2 || player->getFaceDownAt(i)->getCompareValue() == 10 || player->getFaceDownAt(i)->getCompareValue() == 1)
                    {
                        discardStack.push_back(player->getFaceDownAt(i));

                        //Removes the dummy value from the stack
                        if(discardStack.at(0)->getCompareValue() == -1)
                        {
                            discardStack.remove(0);
                        }

                        if((*(discardStack.at(discardStack.size() - 1))).getCompareValue() == 10 || showFourKind)
                        {
                            killPile();

                        }
                        else if(discardStack.at(discardStack.size() - 1)->getCompareValue() == 2)
                        {
                            qDebug() << "Reset Played";
                            showReset = true;
                        }
                        else if(discardStack.at(discardStack.size() - 1)->getCompareValue() == 1)
                        {
                            qDebug() << "CHALLENGE!";
                            showChallenge = true;
                        }
                    }
                    else if(discardStack.at(discardStack.size() - 1)->getCompareValue() <= player->getFaceDownAt(i)->getCompareValue())
                    {
                        discardStack.push_back(player->getFaceDownAt(i));

                        //Removes the dummy value from the stack
                        if(discardStack.at(0)->getCompareValue() == -1)
                        {
                            discardStack.remove(0);
                        }
                    }
                    else
                    {
                        showInvalidMove = true;
                        break;
                    }

                    Card *card = new Card(this);
                    player->replaceCard(0,  i, card);

                    if(player->getFaceDownAt(0)->getCompareValue() == -1 && player->getFaceDownAt(1)->getCompareValue() == -1 && player->getFaceDownAt(2)->getCompareValue() == -1)
                    {
                        player->playerCardsFaceDown.clear();
                        faceDownEmpty = true;
                    }

                    turn++;
                    break;
                }
            }
        }
        else if(handEmpty && shuffledDeck.at(0)->getCompareValue() == -1)
        {
            for(int i = 0; i < 3; i++)
            {
                if((*(player->getFaceUpAt(i))).containsPoint(e->x(), e->y(), QRect(player->getFaceUpAt(i)->getPosX(), player->getFaceUpAt(i)->getPosY(), player->getFaceUpAt(i)->getSizeX(), player->getFaceUpAt(i)->getSizeY())))
                {
                    qDebug() << "Clicked in card" << i << ". Compare Value:" << player->getFaceUpAt(i)->getCompareValue();

                    if(showInvalidMove)
                        showInvalidMove = false;

                    if(showChallenge)
                        showChallenge = false;

                    if(showKillPile)
                        showKillPile = false;

                    if(showReset)
                        showReset = false;

                    if(showFourKind)
                        showFourKind = false;

                    fourCount = 1;

                    for(int j = 0; j < discardStack.size(); j++)
                    {
                        if(player->getFaceDownAt(i)->getCompareValue() == discardStack.at(j)->getCompareValue())
                        {
                            fourCount++;
                        }

                        if(fourCount == 4)
                        {
                            showFourKind = true;
                            break;
                        }
                    }

                    if(player->getFaceUpAt(i)->getCompareValue() == 2 || player->getFaceUpAt(i)->getCompareValue() == 10 || player->getFaceUpAt(i)->getCompareValue() == 1)
                    {
                        discardStack.push_back(player->getFaceUpAt(i));

                        //Removes the dummy value from the stack
                        if(discardStack.at(0)->getCompareValue() == -1)
                        {
                            discardStack.remove(0);
                        }

                        if((*(discardStack.at(discardStack.size() - 1))).getCompareValue() == 10 || showFourKind)
                        {
                            killPile();
                        }
                        else if(discardStack.at(discardStack.size() - 1)->getCompareValue() == 2)
                        {
                            qDebug() << "Reset Played";
                            showReset = true;
                        }
                        else if(discardStack.at(discardStack.size() - 1)->getCompareValue() == 1)
                        {
                            qDebug() << "CHALLENGE!";
                            showChallenge = true;
                        }
                    }
                    else if(discardStack.at(discardStack.size() - 1)->getCompareValue() <= player->getFaceUpAt(i)->getCompareValue())
                    {
                        discardStack.push_back(player->getFaceUpAt(i));

                        //Removes the dummy value from the stack
                        if(discardStack.at(0)->getCompareValue() == -1)
                        {
                            discardStack.remove(0);
                        }
                    }
                    else
                    {
                        showInvalidMove = true;
                        break;
                    }

                    Card *card = new Card(this);
                    player->replaceCard(1,  i, card);

                    turn++;

                    if(player->getFaceUpAt(0)->getCompareValue() == -1 && player->getFaceUpAt(1)->getCompareValue() == -1 && player->getFaceUpAt(2)->getCompareValue() == -1)
                    {
                        player->playerCardsFaceUp.clear();
                        faceUpEmpty = true;
                    }

                    break;
                }
            }
        }
        else if(!handEmpty)
        {
            for(int i = 0; i < player->getNumOfCardsInHand(); i++)
            {
                if((*(player->getCardAt(i))).containsPoint(e->localPos().x(), e->localPos().y(), QRect((*(player->getCardAt(i))).getPosX(), (*(player->getCardAt(i))).getPosY(), (*(player->getCardAt(i))).getSizeX(), (*(player->getCardAt(i))).getSizeY())))
                {
                    qDebug() << "Clicked in card" << i << ". Compare Value:" << player->getCardAt(i)->getCompareValue();

                    if(showInvalidMove)
                        showInvalidMove = false;

                    if(showChallenge)
                        showChallenge = false;

                    if(showKillPile)
                        showKillPile = false;

                    if(showReset)
                        showReset = false;

                    if(showFourKind)
                        showFourKind = false;

                    fourCount = 1;

                    for(int j = 0; j < discardStack.size(); j++)
                    {
                        if(player->getCardAt(i)->getCompareValue() == discardStack.at(j)->getCompareValue())
                        {
                            fourCount++;
                            qDebug() << "Four count:" << fourCount;
                        }

                        if(fourCount == 4)
                        {
                            showFourKind = true;
                            killPile();
                            break;
                        }
                    }

                    if(player->getCardAt(i)->getCompareValue() == 2 || player->getCardAt(i)->getCompareValue() == 10 || player->getCardAt(i)->getCompareValue() == 1)
                    {
                        discardStack.push_back(player->getCardAt(i));

                        //Removes the dummy value from the stack
                        if(discardStack.at(0)->getCompareValue() == -1)
                        {
                            discardStack.remove(0);
                        }

                        if((*(discardStack.at(discardStack.size() - 1))).getCompareValue() == 10 || showFourKind)
                        {
                            killPile();
                        }
                        else if(discardStack.at(discardStack.size() - 1)->getCompareValue() == 2)
                        {
                            qDebug() << "Reset Played";
                            showReset = true;
                        }
                        else if(discardStack.at(discardStack.size() - 1)->getCompareValue() == 1)
                        {
                            qDebug() << "CHALLENGE!";
                            showChallenge = true;
                        }

                        if(player->getNumOfCardsInHand() > 3)
                        {
                            qDebug() << "Removing card at index" << i;
                            player->removeCard(i);
                            goto newTurn;
                        }

                    }
                    //Handles all non-special fuction cards and being able to play aces when a two is the top card in the discard pile and not allow play of non-special cards when an ace is played.
                    else if((discardStack.at(discardStack.size() - 1)->getCompareValue() <= player->getCardAt(i)->getCompareValue() || discardStack.at(discardStack.size() - 1)->getCompareValue() == 2) && !showChallenge)
                    {
                        discardStack.push_back(player->getCardAt(i));

                        //Removes the dummy value from the stack
                        if(discardStack.at(0)->getCompareValue() == -1)
                        {
                            discardStack.remove(0);
                        }

                        if(player->getNumOfCardsInHand() > 3)
                        {
                            qDebug() << "Removing card at index" << i;
                            player->removeCard(i);
                            goto newTurn;
                        }
                    }
                    else
                    {
                        showInvalidMove = true;
                        break;
                    }

                    //Draw Card
                    player->removeCard(i);
                    player->setHand(shuffledDeck.at(0));

                    if(shuffledDeck.size() > 1)
                    {
                        shuffledDeck.erase(shuffledDeck.begin());
                    }
                    else
                    {
                        Card *card = new Card(this);
                        shuffledDeck.push_back(card);
                        shuffledDeck.erase(shuffledDeck.begin());
                    }

                    if(player->hand.at(0)->getCompareValue() == -1 && player->hand.at(1)->getCompareValue() == -1 && player->hand.at(2)->getCompareValue() == -1)
                    {
                        player->hand.clear();
                        handEmpty = true;
                    }
newTurn:
                    turn++;

                    //If the last card removed was the last card in the QVector, do not adjust the card position
                    //This will throw an 'out of range' exception without the 'if' condition statement
                    if(!handEmpty)
                    {
                        if(i < player->getNumOfCardsInHand())
                        {
                            setCardCoord(2, i);
                        }
                    }

                    break;
                }
            }
        }
    }
}//end of mousePressEvent

void BucciGame::killPile()
{
    qDebug() << "Killing Discard";

    showKillPile = true;

    foreach(Card* card, discardStack)
    {
        deadStack.push_back(card);
    }

    //Creates a dummy value to be placed at the end of the vector.
    //This assures that all playable cards are removed from the discard pile,
    //into the correct stack (dead or player hand)
    Card* dummy = new Card(this);
    discardStack.push_back(dummy);

    discardStack.remove(0, discardStack.size() - 1);
}//end of killPile


void BucciGame::setVecs()
{
    //Puts the deck into a vector for game setup

    qDebug() << "Setting up Deck vector";

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            Card *card = new Card(this);
            card->setCardValue(deck->getCardAt(i, j));
            card->initCompareValue(card);
            deckRef.push_back(card);
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
            }
            else
            {
                goto newRand;
            }
        }
        else
        {
            shuffledDeck.push_back(deckRef.at(index));
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
                    (*(player->getFaceDownAt(j))).setX(this->width() / 2 - 66);
                }
                else if(1 == j || 2 == j)
                {
                    (*(player->getFaceDownAt(j))).setX((*(player->getFaceDownAt(j - 1))).getPosX() + 46);
                }

                (*(player->getFaceDownAt(j))).setY(this->height() - (this->height() / 3));

                shuffledDeck.erase(shuffledDeck.begin());
            }
            else if(1 == i)
            {
                player->setFaceUp(shuffledDeck.at(0));

                if(0 == j)
                {
                    (*(player->getFaceUpAt(j))).setX(this->width() / 2 - 66);
                }
                else if(1 == j || 2 == j)
                {
                    (*(player->getFaceUpAt(j))).setX((*(player->getFaceUpAt(j - 1))).getPosX() + 46);
                }

                (*(player->getFaceUpAt(j))).setY(this->height() - (this->height() / 3)  + 15);

                shuffledDeck.erase(shuffledDeck.begin());

            }
            else if(2 == i)
            {
                player->setHand(shuffledDeck.at(0));

                if(0 == j)
                {
                    (*(player->getCardAt(j))).setX(this->width() / 2 - 66);
                }
                else if(1 == j || 2 == j)
                {
                    (*(player->getCardAt(j))).setX((*(player->getCardAt(j - 1))).getPosX() + 46);
                }

                (*(player->getCardAt(j))).setY(this->height() - (this->height() / 3) + 66);

                shuffledDeck.erase(shuffledDeck.begin());
            }
        }
    }

    //===================
    //Sets the first card
    //===================

newCard:
    if(shuffledDeck.at(0)->getCompareValue() == 10 || shuffledDeck.at(0)->getCompareValue() == 1)
    {
        shuffledDeck.insert(shuffledDeck.begin() + 22, shuffledDeck.at(0));
        shuffledDeck.erase(shuffledDeck.begin());
        goto newCard;
    }

    discardStack.push_back(shuffledDeck.at(0));

    shuffledDeck.erase(shuffledDeck.begin());


    qDebug() << "Discard stack:" << (*(discardStack.at(0))).getCardValue();

    qDebug() << "Done";
}//end of setVecs


void BucciGame::setCardCoord(int vector, int index)
{
    int cardsPerRow, cardsPerSecondRow, cardsPerThirdRow, cardsPerFourthRow, cardsPerFifthRow;

    if(player->getNumOfCardsInHand() < 48) //Four rows of cards
    {
        if(player->getNumOfCardsInHand() < 36) //Three rows of cards
        {
            if(player->getNumOfCardsInHand() < 24) //Two rows of cards
            {
                if(player->getNumOfCardsInHand() < 12) //One row of cards
                {
                    cardsPerRow = player->getNumOfCardsInHand();
                }
                else
                {
                    cardsPerRow = 12;
                    cardsPerSecondRow = player->getNumOfCardsInHand() - 15;
                }
            }
            else
            {
                cardsPerRow = 12;
                cardsPerSecondRow = 12;
                cardsPerThirdRow = player->getNumOfCardsInHand() - 39;
            }
        }
        else
        {
            cardsPerRow = 12;
            cardsPerSecondRow = 12;
            cardsPerThirdRow = 12;
            cardsPerFourthRow = player->getNumOfCardsInHand() - 51;
        }
    }
    else
    {
        cardsPerRow = 12;
        cardsPerSecondRow = 12;
        cardsPerThirdRow = 12;
        cardsPerFourthRow = 12;
        cardsPerFifthRow = player->getNumOfCardsInHand() - 55;
    }

    if(0 == vector) // face down
    {
        if(0 == index)
        {
            player->playerCardsFaceDown.at(index)->setX(this->width() / 2 - 66);
        }
        else
        {
            player->playerCardsFaceDown.at(index)->setX(player->getFaceDownAt(index - 1)->getPosX() + 46);
        }

        player->playerCardsFaceDown.at(index)->setY(this->height() - (this->height() / 3));
    }
    else if(1 == vector) //face up
    {
        if(0 == index)
        {
            player->playerCardsFaceUp.at(index)->setX(this->width() / 2 - 66);
        }
        else
        {
            player->playerCardsFaceUp.at(index)->setX(player->playerCardsFaceUp.at(index - 1)->getPosX() + 46);
        }

        player->playerCardsFaceUp.at(index)->setY(this->height() - (this->height() / 3)  +  15);
    }
    else if(2 == vector) //hand
    {
        if(12 > index) //Normal
        {
            if(0 == index)
            {
                //If the player is holding more than three cards, shift the cards 23px to the left per each card over three
                player->hand.at(index)->setX(this->width() / 2 - 66 - (23 * (cardsPerRow - 3)));
            }
            else
            {
                //Each card after the first is 46px to the right of the one before it.
                player->hand.at(index)->setX(player->hand.at(index - 1)->getPosX() + 46);
            }

            player->hand.at(index)->setY(this->height() - (this->height() / 3) + 66);
        }
        else if (24 > index) //Bad luck
        {
            if(12 == index)
            {
                player->hand.at(index)->setX(this->width() / 2 - 66 - (23 * (cardsPerSecondRow)));
            }
            else
            {
                player->hand.at(index)->setX(player->hand.at(index - 1)->getPosX() + 46);
            }

            player->hand.at(index)->setY(this->height() - (this->height() / 3) + 112);
        }
        else if(36 > index) //You're playing the game wrong if you have this many cards in your hand
        {
            if(24 == index)
            {
                player->getCardAt(index)->setX(this->width() / 2 - 66 - (23 * (cardsPerThirdRow)));
            }
            else
            {
                player->getCardAt(index)->setX(player->getCardAt(index - 1)->getPosX() + 46);
            }

            player->hand.at(index)->setY(this->height() - (this->height() / 3) + 158);
        }
        else if (48 > index) //How did you... I don't want to know.
        {
            if(36 == index)
            {
                player->getCardAt(index)->setX(this->width() / 2 - 66 - (23 * cardsPerFourthRow));
            }
            else
            {
                player->getCardAt(index)->setX(player->getCardAt(index - 1)->getPosX() + 46);
            }

            player->hand.at(index)->setY(this->height() - (this->height() / 3) + 204);
        }
        else
        {
            if(48 == index)
            {
                player->getCardAt(index)->setX(this->width() / 2 - 66 - (23 * cardsPerFifthRow));
            }
            else
            {
                player->getCardAt(index)->setX(player->getCardAt(index - 1)->getPosX() + 46);
            }

            player->getCardAt(index)->setY(this->height() - (this->height() / 3) + 250);
        }
    }
}//end of setCardCoord


bool BucciGame::contains(Card* card, QVector<Card *> deck)
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
}//end of contains

void BucciGame::updateField()
{
    this->update();
}//end of updateField


void BucciGame::pickupCards()
{
    if(handEmpty)
    {
        handEmpty = false;
    }

    if(showChallenge)
        showChallenge = false;

    for(int i = 0; i < discardStack.size(); i++)
    {
        qDebug() << i << "of" << discardStack.size();

        //Searches player's hand for any card holding a dummy value.
        //If dummy value is found (comparisonValue == -1), replace it with a card from the discard pile
        //otherwise put the card from the discard stack at the end of the player's hand vector
        if(player->getCardAt(i)->getCompareValue() == -1)
        {
            player->replaceCard(2, i, discardStack.at(i));
        }
        else
        {
            player->setHand(discardStack.at(i));
        }

        player->setNumOfCardsInHand();

        setCardCoord(2, i);

    }

    Card* dummy = new Card(this);
    discardStack.push_back(dummy);

    discardStack.remove(0, discardStack.size() - 1);

}//end of pickupCards

void BucciGame::emptyQueue()
{

}


