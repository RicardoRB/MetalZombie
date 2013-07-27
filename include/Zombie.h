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
    /*!
     * \brief Method to move the character to right
     * \details Add the position of the variable, flip the sprite to right and move the sprite to right
    */
    void moveRight();
    /*!
     * \brief Method to remain player
     * \details Will put the sprite on the first frame and set movingLeft and movingRight false
    */
    void moveRemain();
    /*!
    * \brief Makes the character jump
    * \details Will move up the character in Y direction and will change the boolean if the character did not end jumping
    */
    void jump();
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
    thor::FrameAnimation attack_frames;
private:
};

#endif // ZOMBIE_H
