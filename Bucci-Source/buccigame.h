#ifndef BUCCIGAME_H
#define BUCCIGAME_H

#include <QTimer>
#include <QWidget>
#include <vector>
#include <QRect>
#include "card.h"

class BucciGame : public QWidget
{
    Q_OBJECT
public:
    explicit BucciGame(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    ~BucciGame();

private:
    int turn;
    int cardsInHand;

    vector<Card*>deck;
    vector<Card*>playerCardsFaceDown;
    vector<Card*>playerCardsFaceUp;


    enum cardSuit {SPADE, CLUB, DIAMOND, HEART};
    enum cardValue {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

    QRect drawStack, discardPile, deadPile, playerHand, playerFaceUp, playerFaceDown;
    QTimer *timer;

    Card *card;

    void setVecs();
signals:

public slots:
};

#endif // BUCCIGAME_H
