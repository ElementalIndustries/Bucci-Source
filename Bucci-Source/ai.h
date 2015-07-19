#ifndef AI_H
#define AI_H

#include "player.h"

#include <QTimer>



class AI : public Player
{
public:
    AI();
    ~AI();

private:
    QTimer *timer;
};

#endif // AI_H
