#include "Object.h"
#include <SFML/Audio.hpp>
#ifndef SHOT_H
#define SHOT_H

/*!
 *  \brief     Class of the shot
 *  \details   The shots of the player
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      5/10/2013
 *  \copyright GNU Public License.
 */

class Shot : public Object {
public:
    Shot();
    /*!
    * \brief Call the constructor of the parent class
    * \param file_texture[] char
    */
    Shot(char file_texture[],char file_sound[]);
    virtual ~Shot();
    /*!
     * \brief Return position in X coordinate on window
     * \return float posWindowX
     */
    float getPosWindowX(sf::RenderWindow *_window);
    /*!
     * \brief Return velocity in X coordinate
     * \return float velX
     */
    float getVelX();
    /*!
     * \brief Set the window position in X coordinate
     * \param float _posWIndowX
     */
    void setPosWindowX(float _posWindowX);
    /*!
     * \brief Move the shot to the side left or right
     * \param bool _right
     */
    void moveShot(bool _right);
    /*!
     * \brief Put the show picture away from window
     * \details This method is so usefull when you kill a zombie or go out of window
     */
    void endShot();
    /*!
     * \brief Return true if the object is shot, else will return false
     * \return bool shot
     */
    bool isShot();
    /*!
     * \brief Put the show picture away from window
     * \details This method is so usefull when you kill a zombie or go out of window
     */
    void setShot(bool _shot);
    /*!
     * \brief Return true if the move shot is right and false if going left
     * \return bool directionRight
     */
    bool isDirectionRight();
    /*!
     * \brief Set the direction of the shot
     * \param bool _direction
     */
    void setDirectionRight(bool _direction);
    /*!
     * \brief Play the sound of the shot when is called
     */
    void playShot();
    /*!
    * \details Vector to the picture shot
    */
    sf::IntRect shot_vector;
protected:
private:
    /*!
    * \details If the shot was shot
    */
    bool shot;
    /*!
    * \details If the direction of the shot is Right, true, else false
    */
    bool directionRight;
    /*!
    * \details Velocity in X coordinate
    */
    float velX;
    /*!
    * \details Position in X coordinate on window
    */
    float posWindowX;
    /*!
    * \details Path of the file sound
    */
    char* path_sound;
    /*!
    * \details Buffer of the shot audio effect
    */
    sf::SoundBuffer bufferShot;
    /*!
    * \details Sound of the file shot audio
    */
    sf::Sound soundShot;
};

#endif // SHOT_H
