#ifndef CARD_H
#define CARD_H
#include <QString>
#include <vector>

using namespace std;

class Card
{
public:
    Card();
    ~Card();

    void init();
    void setCardValue(QString value);

    QString getCardAt(int i, int j);
    QString getCardValue();
    QString *getCardPtrValue();


private:
    QString value;
    enum cardSuits {SPADE = 'S', CLUB = 'C', DIAMOND = 'D', HEART = 'H'};
    enum cardValues {ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 11, QUEEN = 12, KING = 13};
};

#endif // CARD_H
