#include "player.h"

Player::Player()
{
    numOfCardsInhand = 0;
}

Player::~Player()
{

}

void Player::setNumOfCardsInHand(int cards)
{
    numOfCardsInhand += cards;
}

void Player::setHand(Card *card)
{
    hand.push_back(card);
}

int Player::getNumOfCardsInHand()
{
    return numOfCardsInhand;
}

Card* Player::getCardAt(int index)
{
    return hand.at(index);
}

