#include "Player.h"
#include <iostream>
#ifndef LEVEL_H
#define LEVEL_H
/*!
 *  \brief     Class of the levels
 *  \details   This class will control the objets of the levels; characters, pictures, sounds, music...
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */

class Level
{
public:
    Level();
    virtual ~Level();
    Player *player1 = new Player();
protected:
private:

};

#endif // LEVEL_H
