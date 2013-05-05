#include "Object.h"
#ifndef SKY_H
#define SKY_H

/*!
 *  \brief     Class of the builders
 *  \details   The sky in the game, is part of the background but you can use it with extras
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      5/05/2013
 *  \copyright GNU Public License.
 */

class Sky : public Object
{
public:
    Sky();
    /*!
    * \brief Call the constructor of the parent class
    * \param file_texture[] char
    */
    Sky(char file_texture[]);
    virtual ~Sky();
protected:
private:
};

#endif // SKY_H
