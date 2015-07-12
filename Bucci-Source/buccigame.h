#ifndef BUCCIGAME_H
#define BUCCIGAME_H

#include <QTimer>
#include <QWidget>
#include <QPixmap>
#include <vector>
#include <QVector>
#include <QRect>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "card.h"
#include "deck.h"
#include "player.h"

class BucciGame : public QWidget
{
    Q_OBJECT
public:
    explicit BucciGame(QWidget *parent = 0);
    ~BucciGame();

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

    bool contains(Card *card, QVector<Card *> deck);

private:
    int turn;

    vector<Card*>deckRef;
    QVector<Card*>shuffledDeck;
    QVector<Card*>discardStack;
    QVector<Card*>deadStack;

    enum cardSuit {SPADE, CLUB, DIAMOND, HEART};
    enum cardValue {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

    QRect drawStack, discardPile, deadPile, playerHand, playerFaceUp, playerFaceDown;
    QTimer *timer;
    QPixmap *cardBack;
    QPushButton *pickup;

    Deck *deck;
    Player *player;

    void setVecs();
    void setCardCoord(int vector, int index);

    QPoint *mousePos;

    bool showInvalidMove;

public slots:
    void updateField();
    void pickupCards();
};

#endif // BUCCIGAME_H
