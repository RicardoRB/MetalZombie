#include "Level.h"
#include "Menu.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
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

class Game {
public:
    /*!
     * \brief Constructor of class Game
     * \details It will create a new level and call the startGame function
    */
    Game();
    virtual ~Game();
    /*!
    * \brief Do the menu begins
    * \details This functions is called to start the menu title
    */
    void startMenu();
    /*!
    * \brief Do the game begins
    * \details This functions is called to start the game
    */
    void startGame();
protected:
private:
    /*!
    * \details The game will have levels
    */
    Level *level1;
    /*!
     * \brief When you call the method, this will take a screenshot of the game windows
     * \details Will take a screenshot of the game with the date and hour in the name
    */
    void takeScreenshot();
    /*!
    * \details The game will have a window
    */
    sf::RenderWindow *window;
    /*!
    * \details Buffer of sound effect of the camera shot
    */
    sf::SoundBuffer bufferCameraShot;
    /*!
    * \details Sound file of the camera shot
    */
    sf::Sound soundCameraShot;
    /*!
    * \details Main menu of the game
    */
    Menu *menuTitle;
    /*!
    * \details Bool to know if the menu is on or not
    */
    bool menu;
    sf::Clock frameClock;
};

#endif // GAME_H
