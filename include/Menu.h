#include "Object.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#ifndef MENU_H
#define MENU_H

/*!
 *  \brief     Class of the title menu
 *  \details   This class will show the menu of the beginning game, with options
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      6/16/2013
 *  \copyright GNU Public License.
 */


class Menu {
public:
    Menu();
    Menu(char text[]);
    virtual ~Menu();
    sf::Text getTextTitle();
    sf::Text getTextStart();
    sf::Text getTextExit();
    Object* getOptionIcon();
    int getOption();
    void setOption(int _option);
    void playSelect();
    void playStart();
protected:
private:
    /*!
    * \details Music in the menu
    */
    sf::Music *music;
    /*!
    * \details Default font file used in the game
    */
    sf::Font font;
    /*!
    * \details Text of the title
    */
    sf::Text titleText;
    /*!
    * \details Text of the start menu
    */
    sf::Text startText;
    /*!
    * \details Text of the exit menu
    */
    sf::Text exitText;
    /*!
    * \details Icon picture to choose options
    */
    Object *optionIcon;
    /*!
    * \details Buffer of the audio's effects
    */
    sf::SoundBuffer *bufferEffect;
    /*!
    * \details Sound of the audio's
    */
    sf::Sound *soundEffect;

    int option;

};

#endif // MENU_H
