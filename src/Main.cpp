#include "../include/Main.h"

/*!
 *  \brief     Main class
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */

using namespace std;

int main()
{
    Game *metalzombie = new Game();
    metalzombie->startGame();
    delete metalzombie;
    return 0;
}
