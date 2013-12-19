#include "../include/Zombie.h"

Zombie::Zombie() {
    //ctor
}

Zombie::Zombie(char file_texture[]) : NPC(file_texture) {
    //ctor
}

Zombie::Zombie(char file_texture[],float _velocityX, float _velocityY, int _lives) : NPC(file_texture) {
    //Add walk animation
    for(int i=214; i<413; i=i+66) {
        this->walk_frames.addFrame(1.f, sf::IntRect(i, 380.f, 55.f, 64.f));
    }
    this->animator.addAnimation("walk", walk_frames, sf::seconds(0.7f));

    //Add dead animation
    for(int i=0; i<608; i=i+152) {
        this->die_frames.addFrame(1.f, sf::IntRect(i, 753.f, 123.f, 152.f));
    }

    for(int i=0; i<609; i=i+729) {
        this->die_frames.addFrame(1.f, sf::IntRect(i, 383.f, 55.f, 65.f));
    }
    this->animator.addAnimation("die", die_frames, sf::seconds(0.5f));

    //Add attack animation
    for(int i=252; i<554; i=i+83) {
        this->attack_frames.addFrame(1.f, sf::IntRect(i, 559.f, 84.f, 77.f));
    }
    this->animator.addAnimation("attack", attack_frames, sf::seconds(1.f));

    //Add remain animation
    for(int i=214 ; i<520; i=i+84) {
        this->remain_frames.addFrame(1.f, sf::IntRect(i, 209.f, 52.f, 63.f));
    }
    this->animator.addAnimation("remain", remain_frames, sf::seconds(1.f));

    this->jump_frames.addFrame(1.f, sf::IntRect(214.f,380.f,55.f,64.f));
    this->animator.addAnimation("jump", jump_frames, sf::seconds(1.f));

    //Zombie
    this->velocity.x = _velocityX;
    this->velocity.y = _velocityY;
    this->getSprite()->setScale(-1.f,1.f);
    this->randomMove = 1;
    this->setVelX(0.f);
    this->setVelY(0.f);
    this->sprite->setTexture(*texture);
    this->sprite->setTextureRect(sf::IntRect(0, 0, 0, 0));
    this->lookRight = false;
    this->lookLeft = true;
    this->life = true;
    this->endJumping = false;
    this->falling = true;
    this->lives = _lives;
}

Zombie::Zombie(sf::Texture* _texture,float _velocityX, float _velocityY, int _lives) : NPC(_texture) {
    //Add walk animation
    for(int i=214; i<413; i=i+66) {
        walk_frames.addFrame(1.f, sf::IntRect(i, 380.f, 55.f, 64.f));
    }
    this->animator.addAnimation("walk", walk_frames, sf::seconds(0.7f));

    //Add dead animation
    for(int i=0; i<608; i=i+152) {
        die_frames.addFrame(1.f, sf::IntRect(i, 753.f, 123.f, 152.f));
    }

    for(int i=0; i<609; i=i+729) {
        die_frames.addFrame(1.f, sf::IntRect(i, 383.f, 55.f, 65.f));
    }
    this->animator.addAnimation("die", die_frames, sf::seconds(0.5f));

    //Add attack animation
    for(int i=252; i<554; i=i+83) {
        attack_frames.addFrame(1.f, sf::IntRect(i, 559.f, 84.f, 77.f));
    }
    this->animator.addAnimation("attack", attack_frames, sf::seconds(1.f));

    //Add remain animation
    for(int i=214 ; i<520; i=i+84) {
        remain_frames.addFrame(1.f, sf::IntRect(i, 209.f, 52.f, 63.f));
    }
    this->animator.addAnimation("remain", remain_frames, sf::seconds(1.f));

    //Zombie
    this->velocity.x = _velocityX;
    this->velocity.y = _velocityY;
    this->getSprite()->setScale(-1.f,1.f);
    this->randomMove = 1;
    this->setVelX(0.f);
    this->setVelY(0.f);
    this->sprite->setTexture(*texture);
    this->sprite->setTextureRect(sf::IntRect(0, 0, 0, 0));
    this->lookRight = false;
    this->lookLeft = true;
    this->life = true;
    this->endJumping = false;
    this->falling = true;
    this->lives = _lives;
}

Zombie::~Zombie() {
    //dtor
    delete sprite;
    delete texture;
}

void Zombie::moveLeft() {
    if(!this->animator.isPlayingAnimation()) {
        this->sprite->setOrigin(27.5f,32.f);
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

void Zombie::moveRight() {
    if(!this->animator.isPlayingAnimation()) {
        this->sprite->setOrigin(27.5f,32.f);
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

void Zombie::attack(Player *_player) {
    this->sprite->setOrigin(42.f,38.5f);
    if(this->animator.getPlayingAnimation() == "walk" || this->animator.getPlayingAnimation() == "remain") {
        this->animator.playAnimation("attack");
    }
    _player->die();
    this->attacking = true;
}

void Zombie::die() {
    this->setVelX(0);
    INIReader file("config.ini");
    if(this->bufferDie.loadFromFile((char*)"res/sounds/effects/characters/npc/enemy/zombies/die.wav")) {
        this->soundDie.setBuffer(this->bufferDie);
        if (file.ParseError() < 0) {
            this->soundDie.setVolume(100.f);
        }else{
            this->soundDie.setVolume(file.GetReal("volume", "effects", 100.f));
        }
        this->soundDie.play();
    }
    this->sprite->setOrigin(77.f,62.f);
    this->animator.playAnimation("die");
    this->movingLeft = false;
    this->movingRight = false;
    this->attacking = false;
    this->life = false;
}

void Zombie::moveRemain() {
    this->setVelX(0);
    this->sprite->setOrigin(27.5f,32.f);
    if(!this->animator.isPlayingAnimation()) {
        this->animator.playAnimation("remain");
    }
    this->movingLeft = false;
    this->movingRight = false;
}

void Zombie::jump() {
    //The player go the maximum position to jump
    this->jumping = true;
    this->falling = false;
    this->endJumping = false;
    this->setVelY(-this->velocity.y);
}

sf::Clock Zombie::getMoveTime() {
    return this->moveTime;
}

void Zombie::resetMoveTime() {
    this->moveTime.restart();
}

int Zombie::getRandomMove() {
    return this->randomMove;
}

void Zombie::setRandomMove(int _randomMove) {
    this->randomMove = _randomMove;
}

int Zombie::getLives() {
    return this->lives;
}

void Zombie::setLives(int _lives) {
    this->lives = _lives;
}
