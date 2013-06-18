#include "Player.h"
#include "Block.h"
#include "Builder.h"
#include "Sky.h"
#include "Zombie.h"
#include <iostream>
#include <sstream>
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

class Level {
public:
    Level();
    /*!
    *  \brief     Constructor overloaded to which you pass the file of music and file of background
    *  \details   Constructor overloaded to which you pass the file of music and file of background, to create a new player and music, playing it and looping it
    */
    Level(char file_music[]);
    virtual ~Level();

    /*!
     * \brief Return the player in the level
     * \return Player*
     */
    Player* getPlayer();

    /*!
    * \details Array of the zombies
    */
    Zombie *zombies[50];
    /*!
    * \details Array of the blocks, static because I need use it with collisions
    */
    Block *blocks[320];
    /*!
    * \details Array of the builders
    */
    Builder *builders[20];
    /*!
    * \details Array of the skies
    */
    Sky *skies[40];

    /*!
    * \details Array of the soldiers friends
    */
    Object *soldiers[10];
    /*!
     * \brief Return the text time
     * \details Text of the time since start level
     * \return sf::Text TextTime
     */
    sf::Text getTextTime();
    /*!
     * \brief Return the text lives
     * \details Text of the rest lives
     * \return sf::Text TextLives
     */
    sf::Text getTextLives();
    /*!
     * \brief Return the text of zombies
     * \details Text of the all zombies dont killed
     * \return sf::Text TextZombies
     */
    sf::Text getTextZombies();
    /*!
     * \brief Return the text of game over
     * \details Text to end game
     * \return sf::Text TextGameOver
     */
    sf::Text getTextGameOver();
    /*!
     * \brief Return the Object livesFace to the IU
     * \details Face picture on UI to lives
     * \return Object* livesFace
     */
    Object* getLivesFace();
    /*!
     * \brief Return the Object ZombiesFace to the IU
     * \details Face Zombie picture on UI to lives
     * \return Object* zombiesFace
     */
    Object* getZombiesFace();
    /*!
     * \brief Return the number of zombies that pass the window
     * \details The numbers of the killed zombies
     * \return int contZombies
     */
    int getContZombies();
    /*!
     * \brief Put the contZombies the number of parameter
     * \param int _contZombies
     */
    void setContZombies(int _contZombies);
    /*!
     * \brief Move the UI on the window
     * \details This method will move all the UI when the player move the camera
     */
    void moveUI();
    void restart();
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
    * \details Background boss, this is not always used
    */
    Object *backgroundBoss;
    /*!
    * \details Lives face picture to the UI
    */
    Object *livesFace;
    /*!
    * \details Zombies face picture to the UI
    */
    Object *zombiesFace;
    /*!
    * \details Default font file used in the game
    */
    sf::Font font;
    /*!
    * \details Text of the time delay
    */
    sf::Text timeText;
    /*!
    * \details Text of lives left
    */
    sf::Text livesText;
    /*!
    * \details Text of all zombies than go away from window
    */
    sf::Text zombiesText;
    /*!
    * \details Text of Game Over
    */
    sf::Text gameOverText;
    /*!
    * \details Clock delay when the level start
    */
    sf::Clock clockTime;
    /*!
    * \details Time to take the seconds of the clock delay when the level start
    */
    sf::Time time;
    /*!
    * \details Count of the how many zombies go away form window
    */
    int contZombies;
    /*!
    * \details Buffer of the audio's effects
    */
    sf::SoundBuffer *bufferEffect;
    /*!
    * \details Sound of the audio's
    */
    sf::Sound *soundEffect;
    /*!
    * \details When the game is finished
    */
    bool endGame;
};

#endif // LEVEL_H
