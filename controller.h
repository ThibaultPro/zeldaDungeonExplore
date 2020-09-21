#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dungeongenerator.h"
#include "levelscene.h"
#include "player.h"

class controller
{
public:
    controller();

private:
    DungeonGenerator *gen;
    Player *Link;

};

#endif // CONTROLLER_H
