#ifndef CARD_H
#define CARD_H
#include <QPainter>
#include <QString>
#include <QPixmap>
#include <vector>
#include <QWidget>

using namespace std;

class Card
{
public:
    Card(QWidget *w);
    ~Card();

    void init();
    void setCardValue(QString newValue);
    void setX(int x);
    void setY(int y);
    void setCompareValue(int cValue);
    void drawCard(QPainter &painter, int vector, QString value);
    void drawCard(QPainter &painter, int vector, QRect rect, QString value);
    void changeImage(QString image);
    void initCompareValue(Card *card);
    void setInQueue();
    void setIndexLoc(int loc);

    QString getCardValue();
    QString getTruncatedValue();

    int getPosX();
    int getPosY();
    int getSizeX();
    int getSizeY();
    int getCompareValue();
    int getIndexLoc();

    bool containsPoint(int x, int y, QRect rect);
    bool equalsValue(Card card, QString compareStr);
    bool getInQueue();

private:
    QString value;
    QPixmap *cardFace;
    int posX, posY, defaultX, defaultY, sizeX, sizeY, compareValue, indexLoc;

    bool inQueue;

    enum cardSuits {SPADE = 'S', CLUB = 'C', DIAMOND = 'D', HEART = 'H'};
    enum cardValues {ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 11, QUEEN = 12, KING = 13};
};

#endif // CARD_H
