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
    hand.erase(hand.begin() + index);
}

void Player::replaceCard(int vector, int index, Card *card)
{
    if(0 == vector)
    {
        playerCardsFaceDown.replace(index, card);
    }
    else if (1 == vector)
    {
        playerCardsFaceUp.replace(index, card);
    }
    else if(2 == vector)
    {
        hand.replace(index, card);
    }
}

int Player::getNumOfCardsInHand()
{
    return numOfCardsInhand;
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

