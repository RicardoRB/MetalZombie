#ifndef LEVELBOSS_H
#define LEVELBOSS_H
#include "Level.h"
#include "ZombieBoss.h"


class LevelBoss : public Level {
public:
    LevelBoss();
    LevelBoss(char background_texture[],char file_music[],float windowWidth, float windowHeight,const unsigned int numZombies,const unsigned int numBlocks);
    virtual ~LevelBoss();
    Object* getBackgroundBoss();
    sf::RectangleShape* getBossLife();
    sf::RectangleShape* getBorderBossLife();
    void reduceLifeBar();
    Object* getTubeBoss();
    void changeTubeSprite();
    ZombieBoss* getBoss();
    void restart(float windowWidth, float windowHeight);
    thor::StopWatch* getTimeTube();
    bool isFirstBlackScreen();
    void setFirstBlackScreen(bool _firstBlackScreen);
    bool isZombiePhase();
    void setZombiePhase(bool _zombiePhase);
    int getDeadZombiesPhase();
    void setDeadZombiesPhase(int _deadZombiesPhase);
protected:
private:
    /*!
    * \details Background boss, this is not always used
    */
    Object *backgroundBoss;
    ZombieBoss *boss;
    sf::RectangleShape *bossLife;
    sf::RectangleShape *borderBossLife;
    Object *tubeBoss;
    thor::StopWatch *timeTube;
    bool firstBlackScreen;
    bool zombiePhase;
    int deadZombiesPhase;

};

#endif // LEVELBOSS_H
