#include "../include/ZombieBoss.h"

ZombieBoss::ZombieBoss() {
    //ctor
}

ZombieBoss::ZombieBoss(char file_texture[],float _velocityX, float _velocityY, int _lives,int _recoverys) : Zombie(file_texture) {

    //Add walk animation
    this->walk_frames.addFrame(1.f, sf::IntRect(34.f, 377.f, 92.f, 105.f));
    this->walk_frames.addFrame(1.f, sf::IntRect(147.f, 377.f, 85.f, 105.f));
    this->walk_frames.addFrame(1.f, sf::IntRect(253.f, 377.f, 94.f, 105.f));
    this->walk_frames.addFrame(1.f, sf::IntRect(368.f, 377.f, 94.f, 105.f));
    this->walk_frames.addFrame(1.f, sf::IntRect(482.f, 377.f, 84.f, 105.f));
    this->walk_frames.addFrame(1.f, sf::IntRect(579.f, 377.f, 78.f, 105.f));
    this->animator.addAnimation("walk", walk_frames, sf::seconds(0.7f));

    //Add dead animation
    this->die_frames.addFrame(1.f, sf::IntRect(32.f, 211.f, 94.f, 110.f));
    this->die_frames.addFrame(1.f, sf::IntRect(200.f, 211.f, 90.f, 110.f));
    this->die_frames.addFrame(1.f, sf::IntRect(320.f, 211.f, 88.f, 110.f));
    this->die_frames.addFrame(1.f, sf::IntRect(423.f, 211.f, 94.f, 110.f));
    this->die_frames.addFrame(1.f, sf::IntRect(546.f, 211.f, 101.f, 110.f));
    this->animator.addAnimation("die", die_frames, sf::seconds(5.f));

    //Add attack animation
    this->attack_frames.addFrame(1.f, sf::IntRect(32.f, 523.f, 118.f, 100.f));
    this->attack_frames.addFrame(1.f, sf::IntRect(165.f, 523.f, 119.f, 100.f));
    this->attack_frames.addFrame(1.f, sf::IntRect(311.f, 523.f, 108.f, 100.f));
    this->attack_frames.addFrame(1.f, sf::IntRect(451.f, 523.f, 88.f, 100.f));
    this->animator.addAnimation("attack", attack_frames, sf::seconds(1.f));

    //Add jump animation
    this->jump_frames.addFrame(1.f, sf::IntRect(305.f,37.f,93.f,121.f));
    this->jump_frames.addFrame(1.f, sf::IntRect(163.f,33.f,93.f,121.f));
    this->jump_frames.addFrame(1.f, sf::IntRect(32.f,45.f,92.f,121.f));
    this->animator.addAnimation("jump", jump_frames, sf::seconds(0.5f));

    //Add hit animation
    this->hit_frames.addFrame(1.f, sf::IntRect(32.f, 209.f, 94.f, 110.f));
    this->animator.addAnimation("hit", hit_frames, sf::seconds(0.3f));

    //Add remain animation
    for(int i=214 ; i<520; i=i+84) {
        this->remain_frames.addFrame(1.f, sf::IntRect(i, 209.f, 52.f, 63.f));
    }
    this->animator.addAnimation("remain", remain_frames, sf::seconds(1.f));

    //Zombie
    this->velocity.x = _velocityX;
    this->velocity.y = _velocityY;
    this->recoverys = _recoverys;
    this->maxRecoverys = _recoverys;
    this->maxLives = _lives;
    this->getSprite()->setScale(-1.f,1.f);
    this->randomMove = 1;
    this->setVelX(0.f);
    this->setVelY(0.f);
    this->sprite->setTexture(*texture);
    this->sprite->setTextureRect(sf::IntRect(0, 0, 0, 0));
    this->lookRight = false;
    this->lookLeft = true;
    this->movingRight = false;
    this->life = true;
    this->endJumping = false;
    this->falling = true;
    this->sprite->setOrigin(47.f,49.f);
    this->lives = _lives;
    this->tube = true;
    this->animator.playAnimation("walk", true);
}

ZombieBoss::~ZombieBoss() {
    //dtor
    delete sprite;
    delete texture;
}

void ZombieBoss::moveRight() {
    if(!this->animator.isPlayingAnimation()) {
        this->sprite->setOrigin(47.f,49.f);
        this->animator.playAnimation("walk", true);
    }
    this->sprite->setScale(1.f,1.f);
    this->lookLeft = false;
    this->lookRight = true;
    this->movingRight = true;
    this->movingLeft = false;
    this->setVelX(this->velocity.x);
    this->attacking = false;
}

void ZombieBoss::moveLeft() {
    if(!this->animator.isPlayingAnimation()) {
        this->sprite->setOrigin(47.f,49.f);
        this->animator.playAnimation("walk", true);
    }
    this->sprite->setScale(-1.f,1.f);
    this->lookLeft = true;
    this->lookRight = false;
    this->movingRight = false;
    this->movingLeft = true;
    this->setVelX(-this->velocity.x);
    this->attacking = false;
}

void ZombieBoss::die() {
    this->setVelX(0);
    if(this->bufferDie.loadFromFile((char*)"res/sounds/effects/characters/npc/enemy/zombies/die.wav")) {
        this->soundDie.setBuffer(this->bufferDie);
        this->soundDie.play();
    }
    this->sprite->setOrigin(47.f,55.f);
    this->animator.playAnimation("die");
    this->movingLeft = false;
    this->movingRight = false;
    this->attacking = false;
    this->life = false;
}

void ZombieBoss::attack(Player *_player) {
    this->sprite->setOrigin(59.5f,50.f);
    if(this->animator.getPlayingAnimation() == "walk" || this->animator.getPlayingAnimation() == "remain") {
        this->animator.playAnimation("attack");
    }
    _player->die();
    this->attacking = true;
}

void ZombieBoss::jump() {
    //The player go the maximum position to jump
    this->sprite->setOrigin(46.f,60.5f);
    this->animator.playAnimation("jump");
    this->jumping = true;
    this->falling = false;
    this->endJumping = false;
    this->setVelY(-this->velocity.y);
}

void ZombieBoss::hit() {
    this->sprite->setOrigin(47.f,55.f);
    this->animator.playAnimation("hit");
    this->setLives(this->getLives() - 1);
}

void ZombieBoss::setTube(bool _tube) {
    this->tube = _tube;
}
bool ZombieBoss::isTube() {
    return this->tube;
}

void ZombieBoss::setRecoverys(int _recoverys) {
    this->recoverys = _recoverys;
}

int ZombieBoss::getRecoverys() {
    return this->recoverys;
}

int ZombieBoss::getMaxLives() {
    return maxLives;
}

int ZombieBoss::getMaxRecoverys() {
    return maxRecoverys;
}
