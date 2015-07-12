#include "card.h"
#include <iostream>
#include <QDebug>

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
}

Card::~Card()
{

}

void Card::setCardValue(QString newValue)
{
    this->value = newValue;
}

void Card::setX(int x)
{
    this->posX = x;
}

void Card::setY(int y)
{
    this->posY = y;
}

void Card::setCompareValue(int cValue)
{
    this->compareValue = cValue;
}

void Card::drawCard(QPainter &painter, int vector, QString value)
{
    bool drawText = false;

    if(0 == vector)//Face Down cards
    {
        changeImage("../Bucci-Source/Images/card_back.png");
        painter.drawPixmap(posX, posY, 30, 40, *cardFace);
        painter.drawRect(posX, posY, 30, 40);
        drawText = false;
    }

    if(1 == vector || 2 == vector)//1 = Face up cards. 2 = Hand
    {
        if(value.contains('S'))
        {
            changeImage("../Bucci-Source/Images/card_spade.png");
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawText = true;
        }
        else if(value.contains('C'))
        {
            changeImage("../Bucci-Source/Images/card_club.png");
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawText = true;
        }
        else if(value.contains('D'))
        {
            changeImage("../Bucci-Source/Images/card_diamond.png");
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawText = true;
        }
        else if(value.contains('H'))
        {
            changeImage("../Bucci-Source/Images/card_heart.png");
            painter.drawPixmap(posX, posY, 30, 40, *cardFace);
            drawText = true;
        }
        else
        {
            drawText = false;
        }

        QString val = value;
        val.truncate(val.indexOf(' '));
        val.insert(0,' ');

        painter.drawRect(posX, posY, 30, 40);

        if(drawText) { painter.drawText(posX, posY + 10, val); }

    }
}

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
}

void Card::changeImage(QString image)
{
//    delete cardFace;
    cardFace = new QPixmap(image);
}

void Card::initCompareValue(Card *card)
{
    QString val = this->value;
    QStringList values = val.split(",", QString::SkipEmptyParts);
    compareValue = values[1].trimmed().toInt();
}

QString Card::getCardValue()
{
    return this->value;
}

QString Card::getTruncatedValue()
{
    QString val = this->value;
    val.truncate(val.indexOf(' '));
    return val;
}

int Card::getPosX()
{
    return this->posX;
}

int Card::getPosY()
{
    return this->posY;
}

int Card::getSizeX()
{
    return this->sizeX;
}

int Card::getSizeY()
{
    return this->sizeY;
}

int Card::getCompareValue()
{
    return compareValue;
}

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
}

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




