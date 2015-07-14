#include "deck.h"
#include <QDebug>
#include <string>

QString deck[4/* Suit */][13/* Card Value */];

Deck::Deck()
{

}//end of Deck c'tor

Deck::~Deck()
{
    qDebug() << "Deck dec'tor called";
    delete[] deck;
}//end of Deck c'tor

void Deck::init()
{
    qDebug() << "Deck Init Called";

    char suit = ' ';
    QString fValue = " ";
    int compareValue = -1;

    for(int j = 0; j < 4; j++)
    {
        if(0 == j)
        {
            suit = SPADE;
        }
        else if(1 == j)
        {
            suit = CLUB;
        }
        else if(2 == j)
        {
            suit = DIAMOND;
        }
        else if(3 == j)
        {
            suit = HEART;
        }

        for(int k = 0; k < 13; k++)
        {
            switch(k + 1)
            {
            case ACE:
                fValue = 'A';
                compareValue = ACE;
                break;
            case TWO:
                fValue = '2';
                compareValue = TWO;
                break;
            case THREE:
                fValue = '3';
                compareValue = THREE;
                break;
            case FOUR:
                fValue = '4';
                compareValue = FOUR;
                break;
            case FIVE:
                fValue = '5';
                compareValue = FIVE;
                break;
            case SIX:
                fValue = '6';
                compareValue = SIX;
                break;
            case SEVEN:
                fValue = '7';
                compareValue = SEVEN;
                break;
            case EIGHT:
                fValue = '8';
                compareValue = EIGHT;
                break;
            case NINE:
                fValue = '9';
                compareValue = NINE;
                break;
            case TEN:
                fValue = "10";
                compareValue = TEN;
                break;
            case JACK:
                fValue = 'J';
                compareValue = JACK;
                break;
            case QUEEN:
                fValue = 'Q';
                compareValue = QUEEN;
                break;
            case KING:
                fValue = 'K';
                compareValue = KING;
                break;
            default:
                fValue = 'N';
                break;
            }

            QString card = QString("%1 %2, %3").arg(fValue).arg(suit).arg(compareValue);

            deck[j][k] = card;
        }
    }

    qDebug() << "Deck init complete";
}//end of init

QString Deck::getCardAt(int i, int j)
{
    return deck[i][j];
}//end of getCardAt

