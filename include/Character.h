#include <SFML/Graphics.hpp>
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

class Character {
public:
    Character();
    virtual ~Character();

    /*!
    * \details Vector to make the animation move
    */
    sf::IntRect image_vector;

    /*!
     * \brief Return the velocity of coordinate X
     * \return Method to return velX
    */
    float getVelX();

    /*!
     * \brief Method to set velY value
     * \param _velY float
    */
    void setVelY(float _velY);

    /*!
    * \brief Method to return movingRight
    * \return Return true if the player is moving right, false if is not
    */
    bool ismovingRight();

    /*!
     * \brief Method to set movingRight true or false
     * \details Method to set movingRight true or false
    */
    void setmovingRight(bool moving);

    /*!
    * \brief Method to return movingLeft
    * \return Return true if the player is moving left, false if is not
    */
    bool ismovingLeft();

    /*!
     * \brief Method to set movingLeft true or false
     * \param moving bool
    */
    void setmovingLeft(bool moving);
    /*!
    * \brief Return if the character is jumping
    * \return Method to return jumping
    */
    bool isJumping();

    /*!
     * \brief Return if the character is end jumping
     * \return Method to return endJumping
    */
    bool isEndJumping();

    /*!
     *\brief Method to set movingLeft true or false
     * \param _endJumping bool
     */
    void setEndJumping(bool _endJumping);

    /*!
     * \brief Return if the character is end attacking
     * \return bool attacking
    */
    bool isAtacking();
    /*!
     *\brief Method to set attacking true or false
     * \param _Attacking bool
     */
    void setAttacking(bool _Attacking);
    /*!
     * \brief Return if the character is looking right
     * \return bool lookingRight
    */
    bool isLookingRight();
    /*!
     * \brief Return if the character is looking left
     * \return bool lookingLeft
    */
    bool isLookingLeft();
    /*!
     * \brief Return if the character is alive
     * \return bool life
    */
    bool isLife();
    /*!
     *\brief Method to set life true or false
     * \param _life bool
     */
    void setLife(bool _life);
    /*!
     * \brief Return the sprite pointer of the character
     * \return sf::Sprite* sprite
    */
    sf::Sprite* getSprite();
    /*!
     * \brief Method that character attack
    */
    virtual void attack();

    /*!
     * \brief Method to move the character to right
     * \details Add the position of the variable, flip the sprite to right and move the sprite to right
    */
    virtual void moveRight();

    /*!
     * \brief Method to move the character to left
     * \details Subtract the position of the variable, flip the sprite to left and move the sprite to left. Is Pure
     * because every character move Left
    */
    virtual void moveLeft() = 0;

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
     * \brief Do the character falling
     * \details Will move down the character in Y direction and will change the boolean if the character did end jumping
    */
    virtual void falling();

    /*!
     * \brief The character die
     * \details Will kill the character. Is pure, because all characters die
    */
    virtual void die() = 0;

protected:
    /*!
    * \details All characters will have texture (picture)
    */
    sf::Texture *texture;

    /*!
    * \details The sprite of the texture
    */
    sf::Sprite *sprite;
    /*!
    * \details If the characters is living, then true, else will be false
    */
    bool life;

    /*!
     * \details If the characters is moving left, then true, else will be false
    */
    bool movingLeft;

    /*!
    * \details If the characters is moving right, then true, else will be false
    */
    bool movingRight;

    /*!
    * \details If the characters is jumping, then true, else will be false
    */
    bool jumping;

    /*!
    * \details If the characters end jumping, then true, else will be false
    */
    bool endJumping;

    /*!
    * \details Velocity of the character in X coordinate
    */
    float velX;

    /*!
    * \details Velocity of the character in Y coordinate
    */
    float velY;

    /*!
    * \details Player position X on the windows
    */
    float posWindowX;

    /*!
    * \details Player position Y on the windows
    */
    float posWindowY;

    /*!
    * \details If the player is attacking then will be true, else, will be false
    */
    bool attacking;
    /*!
    * \details If the player is looking right then will be true, else, will be false
    */
    bool lookRight;

    /*!
    * \details If the player is looking left then will be true, else, will be false
    */
    bool lookLeft;
private:
};

#endif // CHARACTER_H
