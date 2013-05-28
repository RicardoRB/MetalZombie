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

class Shot : public Object
{
public:
    Shot();
    /*!
    * \brief Call the constructor of the parent class
    * \param file_texture[] char
    */
    Shot(char file_texture[],char file_sound[]);
    virtual ~Shot();
    float getPosWindowX();
    float getVelX();
    void setPosWindowX(float _posWindowX);
    void moveShot(bool _right);
    void endShot();
    bool isShot();
    void setShot(bool _shot);
    bool isDirectionRight();
    void setDirectionRight(bool _direction);
    void playShot();
    sf::IntRect shot_vector;
protected:
private:
    bool shot;
    bool directionRight;
    float velX;
    float posWindowX;
    char* path_sound;
    sf::SoundBuffer bufferShot;
    sf::Sound soundShot;
};

#endif // SHOT_H
