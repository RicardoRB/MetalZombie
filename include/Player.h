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


class Player : public Character {
public:
    /*!
    *  \brief     Constructor overloaded to which you pass the file of sprite
    *  \details   Constructor overloaded to which you pass the file of sprite, to take the player on the picture,
    *  \details   to send it on a position on the game window and set the origin of the picture on half-size
    */
    Player(char file_texture[]);
    virtual ~Player();
    /*!
     * \brief Return the camera of the player
     * \return sf::View camera
     */
    sf::View getCamera();
    /*!
     * \brief Set the camera player from the parameter
     * \param sf::View _camera
     */
    void setCamera(sf::View _camera);
    /*!
     * \brief Move the player to right
     */
    void moveRight();
    /*!
     * \brief Move the player to left
     */
    void moveLeft();
    /*!
     * \brief The player will attack
     */
    void attack();
    /*!
     * \brief Return the shot object of the player
     * \return Shot *shot
     */
    Shot* getShot();
    /*!
     * \brief Return the number of lives of the player
     * \return int lives
     */
    int getLives();
    /*!
     * \brief The player will die
     */
    void die();

protected:
private:
    /*!
    * \details Lives of the player
    */
    int lives;
    /*!
    * \details Object shot of the player
    */
    Shot *shot;
    /*!
    * \details Camera to move the player and the view window
    */
    sf::View camera;;
};

#endif // PLAYER_H
