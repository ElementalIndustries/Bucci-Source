#ifndef DECK_H
#define DECK_H

#include <QString>

class Deck
{
public:
    Deck();
    ~Deck();

     QString getCardAt(int i, int j);

     void init();


private:
     enum cardSuits {SPADE = 'S', CLUB = 'C', DIAMOND = 'D', HEART = 'H'};
     enum cardValues {ACE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, TEN = 10, JACK = 11, QUEEN = 12, KING = 13};

};

#endif // DECK_H
