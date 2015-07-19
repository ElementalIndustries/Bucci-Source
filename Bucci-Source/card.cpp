#include "card.h"
#include <iostream>
#include <QDebug>
#include <sstream>
#include <QPainter>

using namespace std;


Card::Card(QWidget *w = 0)
{
    posX = w->width() / 2 - 20;
    posY = w->height() - (w->height() / 3);
    sizeX = 30;
    sizeY = 40;

    cardFace = new QPixmap("../Bucci-Source/Images/card_back.png");

    value = "This is a dummy value";

    compareValue = -1;

    defaultX = w->width() / 2 - 20;
    defaultY = w->height() - (w->height() / 3);

    inQueue = false;
}//end of Card c'tor

Card::~Card()
{
//    qDebug() << "Card dec'tor called";

    delete cardFace;
}//end of card dec'tor

void Card::setCardValue(QString newValue)
{
    this->value = newValue;
}//end of setCardValue

void Card::setX(int x)
{
    this->posX = x;
}//end of setX

void Card::setY(int y)
{
    this->posY = y;
}//end of setY

void Card::setCompareValue(int cValue)
{
    this->compareValue = cValue;
}//end of setCompareValue

void Card::drawCard(QPainter &painter, int vector, QString value)
{
    bool drawText = false, drawRect = true;

    if(0 == vector)//Face Down cards
    {
        changeImage("../Bucci-Source/Images/card_back.png");

        if(!value.contains("This"))
        {
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawRect = false;
        }
        else
        {
            drawRect = true;
        }

        drawText = false;
    }

    if(1 == vector || 2 == vector)//1 = Face up cards. 2 = Hand
    {
        if(value.contains('S'))
        {
            changeImage("../Bucci-Source/Images/card_spade.png");
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawText = true;
            drawRect = true;
        }
        else if(value.contains('C'))
        {
            changeImage("../Bucci-Source/Images/card_club.png");
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawText = true;
            drawRect = true;
        }
        else if(value.contains('D'))
        {
            changeImage("../Bucci-Source/Images/card_diamond.png");
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawText = true;
            drawRect = true;
        }
        else if(value.contains('H'))
        {
            changeImage("../Bucci-Source/Images/card_heart.png");
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawText = true;
            drawRect = true;
        }
        else
        {
            drawText = false;
            drawRect = false;
        }

        QString val = value;
        val.truncate(val.indexOf(' '));
        val.insert(0,' ');


        if(drawRect)
        {
            if(inQueue)
            {
                painter.setPen(Qt::green);
            }
            else
            {
                painter.setPen(Qt::black);
            }

            painter.drawRect(posX, posY, 30, 40);
        }

        if(drawText)
        {
            if(painter.pen().color() == Qt::green)
            {
                painter.setPen(Qt::black);
            }

            painter.drawText(posX, posY + 10, val);
        }


    }
}//end of drawCard

void Card::drawCard(QPainter &painter, int vector, QRect rect, QString value)
{
    if(0 == vector || 2 == vector)//0 = draw pile, 2 == dead pile
    {
        changeImage("../Bucci-Source/Images/card_back.png");
        painter.drawPixmap(rect, *cardFace);
        painter.drawRect(rect);
    }
    else if(1 == vector)//discard pile
    {
        if(value.contains('S'))
        {
            changeImage("../Bucci-Source/Images/card_spade.png");
        }
        else if(value.contains('C'))
        {
            changeImage("../Bucci-Source/Images/card_club.png");
        }
        else if(value.contains('D'))
        {
            changeImage("../Bucci-Source/Images/card_diamond.png");
        }
        else if(value.contains('H'))
        {
            changeImage("../Bucci-Source/Images/card_heart.png");
        }
        else
        {
            changeImage("../Bucci-Source/Images/card_back.png");
        }

        QString val = value;
        val.truncate(val.indexOf(' '));
        val.insert(0,' ');
        painter.drawPixmap(rect, *cardFace);
        painter.drawRect(rect) ;
        painter.drawText(rect, val);
    }
}//end of drawCard overloaded method

void Card::changeImage(QString image)
{
    delete cardFace;
    cardFace = new QPixmap(image);
}//end of changeImage

void Card::initCompareValue(Card *card)
{
    stringstream ss(value.toStdString());
    if((ss >> compareValue))
    {
        QString val = this->value;
        QStringList values = val.split(",", QString::SkipEmptyParts);
        card->setCompareValue(values[1].trimmed().toInt());
        qDebug() << compareValue;
    }
}

void Card::setInQueue()
{
    inQueue = !inQueue;
}

void Card::setIndexLoc(int loc)
{
    this->indexLoc = loc;
}//end of initCompareValue

QString Card::getCardValue()
{
    return this->value;
}//end of getCardValue

QString Card::getTruncatedValue()
{
    QString val = this->value;
    val.truncate(val.indexOf(' '));
    return val;
}//end of getTruncatedValue

int Card::getPosX()
{
    return this->posX;
}//end of getPosX

int Card::getPosY()
{
    return this->posY;
}//end of getPosY

int Card::getSizeX()
{
    return this->sizeX;
}//end of getSizeX

int Card::getSizeY()
{
    return this->sizeY;
}//end of getSizeY

int Card::getCompareValue()
{
    return compareValue;
}

int Card::getIndexLoc()
{
    return indexLoc;
}//end of getCompareValue

bool Card::containsPoint(int x, int y, QRect rect)
{
    if(rect.topLeft().y() < y && rect.bottomLeft().y() > y)
    {
        if(rect.topRight().x() > x && rect.topLeft().x() < x)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}//end of contains point

bool Card::equalsValue(Card card, QString compareStr)
{
    if(card.getCardValue().startsWith(compareStr))
    {
        qDebug() << "True";
        return true;
    }
    else
        return false;
}

bool Card::getInQueue()
{
    return inQueue;
}//end of equalsValue




