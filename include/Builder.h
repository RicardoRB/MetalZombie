#include "Object.h"
#ifndef BUILDER_H
#define BUILDER_H

/*!
 *  \brief     Class of the builders
 *  \details   Builders in the game, is part of the background but you can use it with extras
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      5/03/2013
 *  \copyright GNU Public License.
 */

class Builder : public Object
{
public:
    Builder();
    /*!
     * \brief Call the constructor of the parent class
     * \param file_texture[] char
     */
    Builder(char file_texture[]);
    virtual ~Builder();
protected:
private:
};

#endif // BUILDER_H
