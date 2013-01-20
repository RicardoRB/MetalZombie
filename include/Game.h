#include "Level.h"
#include <iostream>
#ifndef GAME_H
#define GAME_H
/*!
 *  \brief     Class of the game
 *  \details   This class will control and execute the game, like windows and events
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */

class Game
{
public:
    Game();
    virtual ~Game();
    /*!
    * \brief Do the game beging
    * \details This fuctions is called to start the game
    */
    void startGame();
protected:
private:
    Level *level1 = new Level();
    sf::RenderWindow window;
};

#endif // GAME_H
