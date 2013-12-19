#ifndef LEVEL_H
#define LEVEL_H
#include "Player.h"
#include "Zombie.h"
#include "Menu.h"
#include "INIReader.h"
#include <Thor/Time.hpp>
#include <sstream>
#include <vector>
#include <ctime>
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
    Level(char file_music[],float windowWidth, float windowHeight,const unsigned int numZombies,const unsigned int numBlocks,const unsigned int numBuilders,const unsigned int numSkies,const unsigned int numSoldiers);
    virtual ~Level();

    const float gravity = 980.f;

    /*!
     * \brief Return the player in the level
     * \return Player*
     */
    Player* getPlayer();

    /*!
    * \details Array of the zombies
    */
    std::vector<Zombie*> zombies;
    /*!
    * \details Array of the blocks
    */
    std::vector<Object*> blocks;
    /*!
    * \details Array of the platforms
    */
    std::vector<Object*> platforms;
    /*!
    * \details Array of the builders
    */
    std::vector<Object*> builders;
    /*!
    * \details Array of the skies
    */
    std::vector<Object*> skies;

    /*!
    * \details Array of the soldiers friends
    */
    std::vector<Object*> soldiers;
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
     * \brief Return the text of FPS
     * \return sf::Text TextFPS
     */
    sf::Text getTextFPS();
    /*!
     * \brief Return the text of Resume
     * \return sf::Text TextResume
     */
    sf::Text getTextResume();
    /*!
     * \brief Return the text of Quit
     * \return sf::Text TextQuit
     */
    sf::Text getTextExit();
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
     * \brief Return the Object joystickImage to the IU
     * \details Joystick picture on UI
     * \return Object* joystickImage
     */
    Object* getJoystickImage();
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
    void moveUI(sf::RenderWindow *_window);
    void restart(float windowWidth, float windowHeight);
    void verticalSpeed(Character *_character, float speedY);
    void horizontalSpeed(Character *_character, float MaxSpeedX, float decreaseX);
    float getFPS();
    void setFPS(float _fps);
    void blockCollision(Character *_character,std::vector<Object*> _blocks);
    bool isLevelPause();
    void pauseLevel();
    void resumeLevel();
    Menu* getPauseMenu();
    float getClockSeconds();
    sf::Music* getMusic();
protected:
    /*!
    * \details Player in the level
    */
    Player *player1;
    /*!
    * \details Music in the level
    */
    sf::Music *music;
    /*!
    * \details Lives face picture to the UI
    */
    Object *livesFace;
    /*!
    * \details Zombies face picture to the UI
    */
    Object *zombiesFace;
    /*!
    * \details Zombies face picture to the UI
    */
    Object *joystickImage;
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
    * \details Text of FPS
    */
    sf::Text FPSText;
    /*!
    * \details Text of Resume
    */
    sf::Text ResumeText;
    /*!
    * \details Text of Exit
    */
    sf::Text ExitText;
    /*!
    * \details Clock delay when the level start
    */
    thor::StopWatch clockTime;
    /*!
    * \details Count of the how many zombies go away form window
    */
    int contZombies;
    /*!
    * \details Buffer of the audio's effects
    */
    sf::SoundBuffer bufferEffect;
    /*!
    * \details Sound of the audio's
    */
    sf::Sound soundEffect;
    /*!
    * \details When the game is finished
    */
    bool endGame;
    float fps;
    Menu *pauseMenu;
private:
};

#endif // LEVEL_H
