#ifndef ZOMBIEBOSS_H
#define ZOMBIEBOSS_H
#include "Zombie.h"


class ZombieBoss : public Zombie {
public:
    ZombieBoss();
    ZombieBoss(char file_texture[],float _velocityX, float _velocityY, int _lives,int _recoverys);
    virtual ~ZombieBoss();
    void moveRight();
    void moveLeft();
    void die();
    void attack(Player *_player);
    void jump();
    void hit();
    void setTube(bool _tube);
    bool isTube();
    void setRecoverys(int _recoverys);
    int getRecoverys();
    int getMaxLives();
    int getMaxRecoverys();
protected:
private:
    bool tube;
    int recoverys;
    thor::FrameAnimation hit_frames;
    int maxLives;
    int maxRecoverys;
};

#endif // ZOMBIEBOSS_H
