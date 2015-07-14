#include "player.h"
#include <QDebug>
#include <QWidget>

Player::Player()
{
    numOfCardsInhand = 0;

}//end of player c'tor

Player::~Player()
{
    qDebug() << "Player dec'tor called";

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
}//end of player dec'tor

void Player::setNumOfCardsInHand()
{
    numOfCardsInhand = hand.size();
}//end of setNumOfCardsInHand()

void Player::setHand(Card *card)
{
    hand.push_back(card);
}//end of setHand

void Player::setFaceDown(Card *card)
{
    playerCardsFaceDown.push_back(card);
}//end of setFaceDown

void Player::setFaceUp(Card *card)
{
    playerCardsFaceUp.push_back(card);
}//end of setFaceUp

void Player::removeCard(int index)
{
    hand.erase(hand.begin() + index);
}//end of remove card

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
}//end of replace card

int Player::getNumOfCardsInHand()
{
    return hand.size();
}//end of getNumOfCardsInHand

int Player::getNumOfFaceUps()
{
    return playerCardsFaceUp.size();
}//end of getNumOfFaceUps

Card* Player::getCardAt(int index)
{
    return hand.at(index);
}//end of getCardAt

Card* Player::getFaceUpAt(int index)
{
    return playerCardsFaceUp.at(index);
}//end of getFaceUpAt

Card *Player::getFaceDownAt(int index)
{
    return playerCardsFaceDown.at(index);
}//end of getFaceDownAt

bool Player::isHandEmpty()
{
    return hand.empty();
}//end of isHandEmpty

bool Player::isFaceUpEmpty()
{
    return playerCardsFaceUp.empty();
}//end of isFaceUpEmpty

bool Player::isFaceDownEmpty()
{
    return playerCardsFaceDown.empty();
}//end of isFaceDownEmpty

