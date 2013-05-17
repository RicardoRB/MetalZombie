#include "Character.h"
#include "Shot.h"
#ifndef PLAYER_H
#define PLAYER_H
/*!
 *  \brief     Class of the players
 *  \details   This class will be the players that the user will control
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */


class Player : public Character
{
public:
    /*!
    *  \brief     Constructor overloaded to which you pass the file of sprite
    *  \details   Constructor overloaded to which you pass the file of sprite, to take the player on the picture,
    *  \details   to send it on a position on the game window and set the origin of the picture on half-size
    */
    Player(char file_texture[]);
    virtual ~Player();
    sf::View camera;
    void moveRight();
    void moveLeft();
    void attack();
    float getPosWindowX();
    Shot* getShot();
protected:
private:
    Shot *shot;
    /*!
    * \details Player position X on the windows
    */
    float posWindowX;

    /*!
    * \details Player position Y on the windows
    */
    float posWindowY;
};

#endif // PLAYER_H
