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

class Object {
public:
    Object();
    /*!
     * \brief Call the constructor of the parent class
     * \param file_texture[] char
     */
    Object(char file_texture[]);
    Object(sf::Texture* _texture);
    virtual ~Object();
    /*!
    * \brief Return the sprite of the object
    * \return sf::Sprite*
    */
    sf::Sprite* getSprite();
    /*!
    * \brief Return tIntRect to the picture position
    * \return sf::IntRect
    */
    sf::IntRect getObjectVector();
    /*!
    * \brief Put the vector to the vector of the param
    * \param sf::IntRect _rect
    */
    void setObjectVector(sf::IntRect _rect);
    void changeTexture(char file_texture[]);
    sf::Texture* getTexture();
protected:
    /*!
    * \details Texture of the object
    */
    sf::Texture *texture;
    /*!
    * \details Sprite of the object
    */
    sf::Sprite *sprite;
    /*!
    * \details Vector of the object
    */
    sf::IntRect objectVector;
private:

};

#endif // OBJECT_H
