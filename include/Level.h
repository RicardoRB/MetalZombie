#include "Player.h"
#include "Block.h"
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
    Player *player1 = NULL;
    sf::Music *music = NULL;
    sf::Texture backgroundImage;
    sf::Sprite background;
    Block *blocks[32];
protected:
private:

};

#endif // LEVEL_H
