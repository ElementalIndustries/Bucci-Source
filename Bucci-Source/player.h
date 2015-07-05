#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <vector>


class Player
{
public:
    Player();
    ~Player();

    void setNumOfCardsInHand(int cards);
    void setHand(Card* card);

    int getNumOfCardsInHand();
    Card *getCardAt(int index);

private:
    int numOfCardsInhand;
    vector<Card*>hand;
};

#endif // PLAYER_H
