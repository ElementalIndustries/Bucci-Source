#include "player.h"
#include <QDebug>
#include <QWidget>

Player::Player()
{
    numOfCardsInhand = 0;
}

Player::~Player()
{
    if(!playerCardsFaceDown.empty())
    {
        playerCardsFaceDown.clear();
    }

    if(!playerCardsFaceUp.empty())
    {
        playerCardsFaceUp.clear();
    }

    if(!hand.empty())
    {
        hand.clear();
    }
}

void Player::setNumOfCardsInHand()
{
    numOfCardsInhand = hand.size();
}

void Player::setHand(Card *card)
{
    hand.push_back(card);
}

void Player::setFaceDown(Card *card)
{
    playerCardsFaceDown.push_back(card);
}

void Player::setFaceUp(Card *card)
{
    playerCardsFaceUp.push_back(card);
}

void Player::removeCard(int index)
{
    foreach(Card* card, hand) qDebug() << "Before" << card->getCardValue();
    qDebug() << "============";
    hand.removeAt(index);
    foreach(Card* card, hand) qDebug() << "After" << card->getCardValue();
}

void Player::replaceCard(int index, Card *card)
{
    hand.replace(index, card);
}

void Player::setCardCoordAt(int vector, int index, QWidget *w)
{
    if(0 == vector) //face down
    {
        if(0 == index)
        {
            (*(hand.at(index))).setX(w->width() / 2 - 55);
        }
        else if(1 == index || 2 == index)
        {
            (*(hand.at(index))).setX((*(hand.at(index - 1))).getPosX() + 45);
        }

        (*(hand.at(index))).setY(w->height() - (w->height() / 3));
    }
    else if(1 == vector) //face up
    {
        if(0 == index)
        {
            (*(hand.at(index))).setX(w->width() / 2 - 55);
        }
        else if(1 == index || 2 == index)
        {
            (*(hand.at(index))).setX((*(hand.at(index - 1))).getPosX() + 45);
        }

        (*(hand.at(index))).setY(w->height() - (w->height() / 3) + 15);
    }
    else if(2 == vector) //hand
    {
        if(0 == index)
        {
            (*(hand.at(index))).setX(w->width() / 2 - 55);
        }
        else if(1 == index || 2 == index)
        {
            (*(hand.at(index))).setX((*(hand.at(index - 1))).getPosX() + 45);
        }

        (*(hand.at(index))).setY(w->height() - (w->height() / 3) + 65);
    }
}

int Player::getNumOfCardsInHand()
{
    return hand.size();
}

int Player::getNumOfFaceUps()
{
    return playerCardsFaceUp.size();
}

Card* Player::getCardAt(int index)
{
    return hand.at(index);
}

Card* Player::getFaceUpAt(int index)
{
    return playerCardsFaceUp.at(index);
}

Card *Player::getFaceDownAt(int index)
{
    return playerCardsFaceDown.at(index);
}

bool Player::isHandEmpty()
{
    return hand.empty();
}

bool Player::isFaceUpEmpty()
{
    return playerCardsFaceUp.empty();
}

bool Player::isFaceDownEmpty()
{
    return playerCardsFaceDown.empty();
}

