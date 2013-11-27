#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "Shot.h"
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
    Player();
    /*!
    *  \brief     Constructor overloaded to which you pass the file of sprite
    *  \details   Constructor overloaded to which you pass the file of sprite, to take the player on the picture,
    *  \details   to send it on a position on the game window and set the origin of the picture on half-size
    */
    Player(char file_texture[], float _windowWidth);
    Player(sf::Texture* _texture, float _windowWidth);
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
     * \brief Return the sprite position in window
     * \return float posWindowX
    */
    float getPosWindowX(sf::RenderWindow *_window);
    /*!
     * \brief Move the player to right
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
    bool isEndLevel();
    void setEndLevel(bool _endLevel);

protected:
private:
    /*!
    * \details Player position X on the windows
    */
    float posWindowX;

    /*!
    * \details Player position Y on the windows
    */
    float posWindowY;
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
    sf::View camera;
    /*!
    * \details Buffer of the die audio effect
    */
    sf::SoundBuffer bufferDie;
    /*!
    * \details Sound of the file die audio
    */
    sf::Sound soundDie;
    float windowWidth;
    bool endLevel;
};

#endif // PLAYER_H
