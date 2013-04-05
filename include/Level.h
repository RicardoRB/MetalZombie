#include "Player.h"
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
    *  \brief     Constructor overloaded to which you pass the file of music
    *  \details   Constructor overloaded to which you pass the file of music, to create a new player and music, playing it and looping it
    */
    Level(char file_music[]);
    virtual ~Level();
    Player *player1 = NULL;
    sf::Music *music = NULL;
protected:
private:

};

#endif // LEVEL_H
