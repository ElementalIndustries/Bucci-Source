#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <QVector>


class Player
{
public:
    Player();
    ~Player();

    void setNumOfCardsInHand();
    void setHand(Card *card);
    void setFaceDown(Card *card);
    void setFaceUp(Card *card);
    void removeCard(int index);
    void replaceCard(int index, Card* card);

    int getNumOfCardsInHand();
    int getNumOfFaceUps();

    Card* getCardAt(int index);
    Card* getFaceUpAt(int index);
    Card* getFaceDownAt(int index);

    bool isHandEmpty();
    bool isFaceUpEmpty();
    bool isFaceDownEmpty();

    QVector<Card*>hand;
    QVector<Card*>playerCardsFaceDown;
    QVector<Card*>playerCardsFaceUp;
private:
    int numOfCardsInhand;
};

#endif // PLAYER_H
