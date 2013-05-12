#include <SFML/Graphics.hpp>
#ifndef OBJECT_H
#define OBJECT_H

/*!
 *  \brief     Class of all objects
 *  \details   This class is the parent class of the all objects in the game
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */

class Object
{
public:
    Object();
    Object(char file_texture[]);
    virtual ~Object();
    /*!
     * \brief Return the sprite of the object
     * \return sf::Sprite*
     */
    sf::Sprite* getSpriteObject();
protected:
private:
    /*!
    * \details Texture of the object
    */
    sf::Texture *objectImage;
    /*!
    * \details Sprite of the object
    */
    sf::Sprite *object;
};

#endif // OBJECT_H
