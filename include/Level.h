#include "Player.h"
#include "Block.h"
#include "Builder.h"
#include "Sky.h"
#include <SFML/Audio.hpp>
#ifndef LEVEL_H
#define LEVEL_H
/*!
 *  \brief     Class of the levels
 *  \details   This class will control the objects of the levels; characters, pictures, sounds, music...
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */

class Level
{
public:
    Level();
    /*!
    *  \brief     Constructor overloaded to which you pass the file of music and file of background
    *  \details   Constructor overloaded to which you pass the file of music and file of background, to create a new player and music, playing it and looping it
    */
    Level(char file_music[], char file_image[]);
    virtual ~Level();

    /*!
     * \brief Return the player in the level
     * \return Player*
     */
    Player* getPlayer();
    /*!
     * \brief Return the sprite of the builders
     * \return sf::Sprite
     */
    sf::Sprite getBuilders();
    /*!
    * \details Array of the blocks, static because I need use it with collisions
    */
    Block *blocks[50];
    /*!
    * \details Array of the builders
    */
    Builder *builders[20];

    /*!
    * \details Array of the skies
    */
    Sky *skies[40];
protected:
private:
    /*!
    * \details Player in the level
    */
    Player *player1;
    /*!
    * \details Music in the level
    */
    sf::Music *music;
    /*!
    * \details Background texture, this is not always used
    */
    sf::Texture backgroundImage;
    /*!
    * \details Background sprite, this is not always used
    */
    sf::Sprite background;
};

#endif // LEVEL_H
