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

class Character
{
public:
    Character();
    virtual ~Character();
    /*!
     * \details life If the characters is living, then true, else will be false
    */
    bool life = true;
    float velX;
    float velY;
    int posX;
    int posY;
    /*!
    * \brief Put the character in the initial position
    * \details Is virtual because not all the characters start in the same position
    */
    void posInit();
    /*!
     * \brief Main attack of the characters
     * \details Is virtual because not all the characters attack at the same way
    */
    void attack();
    /*!
     * \brief Main attack of the characters
     * \details Is virtual because not all the characters attack at the same way
     * \param posX The position in X coordinate to move the character
     * \return True if the character is moving right
    */
    bool moveRight(int &posX)
    {
        posX++;
        return true;
    }
    /*!
     * \brief Main attack of the characters
     * \details Is virtual because not all the characters attack at the same way
     * \param posX The position in X coordinate to move the character
     * \return True if the character is moving left
    */
    bool moveLeft(int &posX)
    {
        posX--;
        return true;
    }
protected:
private:
};

#endif // CHARACTER_H
