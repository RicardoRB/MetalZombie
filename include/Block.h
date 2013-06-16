#include "Object.h"
#ifndef BLOCK_H
#define BLOCK_H

/*!
 *  \brief     Class of blocks
 *  \details   Blocks in the game, can be used to collisions with players
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      5/03/2013
 *  \copyright GNU Public License.
 */

class Block : public Object {
public:
    Block();
    /*!
    * \brief Call the constructor of the parent class
    * \param file_texture[] char
    */
    Block(char file_texture[]);
    virtual ~Block();
protected:
private:
};

#endif // BLOCK_H
