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

class Zombie : public NPC {
public:
    Zombie();
    /*!
    * \brief Call the constructor of the parent class
    * \param file_texture[] char
    */
    Zombie(char file_texture[]);
    /*!
     * \brief Method to move the zombie to left
     * \details Subtract the position of the variable, flip the sprite to left and move the sprite to left.
    */
    void moveLeft();
    virtual ~Zombie();
    /*!
     * \brief Attack the player passed
     * \details This zombie method need
     * \param Player *_player
    */
    void attack(Player *_player);
    /*!
     * \brief The zombie die
     * \details Will kill the zombie
    */
    void die();
protected:
private:

};

#endif // ZOMBIE_H
