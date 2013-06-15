#include "Character.h"
#ifndef NPC_H
#define NPC_H

/*!
 *  \brief     Class of the non-players character
 *  \details   This class will take the logic to interact with players
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      5/15/2013
 *  \copyright GNU Public License.
 */

class NPC : public Character {
public:
    NPC();
    virtual ~NPC();
protected:
private:
};

#endif // NPC_H
