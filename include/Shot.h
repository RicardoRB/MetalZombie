#include "Object.h"
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
    Shot(char file_texture[]);
    virtual ~Shot();
    float getPosWindowX();
    float getVelX();
    void setPosWindowX(float _posWindowX);
    sf::IntRect shot_vector;
protected:
private:
    float velX;
    float posWindowX;
};

#endif // SHOT_H
