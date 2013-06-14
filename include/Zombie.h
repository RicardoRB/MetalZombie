#include "NPC.h"
#include "Player.h"
#include <iostream>
#ifndef ZOMBIE_H
#define ZOMBIE_H
/*!
 *  \brief     Class of the main enemy's, Zombies
 *  \details   This class will be the enemy's of the game, a parent class of all zombies
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */

class Zombie : public NPC
{
public:
    Zombie();
    Zombie(char file_texture[]);
    void moveLeft();
    virtual ~Zombie();
    void attack(Player *_player);
    void die();
protected:
private:
};

#endif // ZOMBIE_H
