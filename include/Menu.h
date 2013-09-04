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
    Menu(float windowWidth, float windowHeight);
    virtual ~Menu();
    /*!
     * \brief Return the titleText from menu
     * \return sf::Text titleText
     */
    sf::Text getTextTitle();
    /*!
     * \brief Return the startText from menu
     * \return sf::Text startText
     */
    sf::Text getTextStart();
    /*!
     * \brief Return the exitText from menu
     * \return sf::Text exitText
     */
    sf::Text getTextExit();
    /*!
     * \brief Return the object option to draw it
     * \return Object *optionIcon
     */
    Object* getOptionIcon();
    /*!
     * \brief Return the number option choosed
     * \return int option
     */
    int getOption();
    /*!
     * \brief Set the option number
     * \param int _option
     */
    void setOption(int _option);
    /*!
     * \brief Play the select sound effect
     */
    void playSelect();
    /*!
     * \brief Play the start sound effect
     */
    void playStart();
    Object* getIntroLogo();
    Object* getIntroLogoCC();
    void playIntroMenu();
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
    /*!
    * \details Number option to choose it
    */
    int option;
    Object *introLogo;
    Object *introLogoCC;

};

#endif // MENU_H
