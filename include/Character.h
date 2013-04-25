#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef CHARACTER_H
#define CHARACTER_H
/*!
 *  \brief     Class of characters
 *  \details   This class is the parent class of the all characters in the game
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */

class Character
{
public:
    Character();
    virtual ~Character();
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect image_vector;

    /*!
    * \brief Put the character in the initial position
    * \details Is virtual because not all the characters start in the same position
    */
    virtual void posInit();

    /*!
     * \brief Main attack of the characters
     * \details Is virtual because not all the characters attack at the same way
    */
    void attack();

    /*!
     * \brief Function to move the character to right
     * \details Add the position of the variable, flip the sprite to right and move the sprite to right
    */
    void moveRight();

    /*!
     * \brief Function to return movingRight
     * \return Return true if the player is moving right, false if is not
    */
    bool ismovingRight();

    /*!
     * \brief Function to set movingRight true or false
     * \details Function to set movingRight true or false
    */
    void setmovingRight(bool moving);

    /*!
     * \brief Function to move the character to left
     * \details Subtract the position of the variable, flip the sprite to left and move the sprite to left
    */
    void moveLeft();

    /*!
     * \brief Function to return movingLeft
     * \return Return true if the player is moving left, false if is not
    */
    bool ismovingLeft();

    /*!
     * \brief Function to set movingLeft true or false
     * \details Function to set movingLeft true or false
    */
    void setmovingLeft(bool moving);

    /*!
     * \brief Function to remain player
     * \details Will put the sprite on the first frame and set movingLeft and movingRight false
    */
    void moveRemain();

    /*!
     * \brief Return the velocity of coordinate X
     * \return Function to return velX
    */
    float getVelX();
    /*!
     * \brief Makes the character jump
     * \details Will move up the character in Y direction and will change the boolean if the character did not end jumping
    */
    void jump();

    /*!
     * \brief Do the character falling
     * \details Will move down the character in Y direction and will change the boolean if the character did end jumping
    */
    void falling();

    /*!
     * \brief Return if the character is jumping
     * \return Function to return jumping
    */
    bool isJumping();

    /*!
     * \brief Return if the character is end jumping
     * \return Function to return endJumping
    */
    bool isEndJumping();

protected:
private:
    /*!
     * \details If the characters is living, then true, else will be false
    */
    bool life = true;

    /*!
     * \details If the characters is moving left, then true, else will be false
    */
    bool movingLeft = false;

    /*!
    * \details If the characters is moving right, then true, else will be false
    */
    bool movingRight = false;

    /*!
    * \details If the characters is jumping, then true, else will be false
    */
    bool jumping = false;

    /*!
    * \details If the characters end jumping, then true, else will be false
    */
    bool endJumping = true;

    /*!
    * \details Velocity of the character in X coordinate
    */
    float velX = 0;

    /*!
    * \details Velocity of the character in Y coordinate
    */
    float velY = 0;

    /*!
    * \details Position of the character in X coordinate
    */
    float posX = 0;

    /*!
    * \details Position of the character in X coordinate
    */
    float posY = 0;

};

#endif // CHARACTER_H
