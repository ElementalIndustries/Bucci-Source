#include "card.h"
#include <iostream>
#include <QDebug>

using namespace std;

QString deck[4][13];

Card::Card()
{
    value = " ";
}

Card::~Card()
{
//    delete value;
}

void Card::init()
{
    qDebug() << "init called";

    char suit = NULL;
    int value = NULL;

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
                value = ACE;
                break;
            case TWO:
                value = TWO;
                break;
            case THREE:
                value = THREE;
                break;
            case FOUR:
                value = FOUR;
                break;
            case FIVE:
                value = FIVE;
                break;
            case SIX:
                value = SIX;
                break;
            case SEVEN:
                value = SEVEN;
                break;
            case EIGHT:
                value = EIGHT;
                break;
            case NINE:
                value = NINE;
                break;
            case TEN:
                value = TEN;
                break;
            case JACK:
                value = JACK;
                break;
            case QUEEN:
                value = QUEEN;
                break;
            case KING:
                value = KING;
                break;
            }

            QString card = QString("%1%2").arg(value).arg(suit);

            deck[j][k] = card;

        }
    }
}

void Card::setCardValue(QString value)
{
//    delete this->value;
    this->value = value;
}

QString Card::getCardAt(int i, int j)
{
    return deck[i][j];
}

QString Card::getCardValue()
{
    return value;
}




