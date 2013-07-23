#include "../include/Zombie.h"

Zombie::Zombie() {
    //ctor
}

Zombie::Zombie(char file_texture[]) {
    sf::Image image;
    if (!image.loadFromFile(file_texture)) {
        //        std::cout << "Error file texture player" << std::endl;
    } else {
        image.createMaskFromColor(sf::Color::Transparent);
        texture->loadFromImage(image);
    }
    //Add walk animation
    for(int i=214; i<413; i=i+66) {
        walk_frames.addFrame(1.f, sf::IntRect(i, 383, 55, 66));
    }
    this->animator.addAnimation("walk", walk_frames, sf::seconds(0.7f));

    //Add dead animation
    for(int i=0; i<608; i=i+152) {
        die_frames.addFrame(1.f, sf::IntRect(i, 753, 123, 152));
    }

    for(int i=0; i<609; i=i+729) {
        die_frames.addFrame(1.f, sf::IntRect(i, 383, 55, 65));
    }

    this->animator.addAnimation("die", die_frames, sf::seconds(0.5f));
    //Player
    this->sprite->setTexture(*texture);
    this->sprite->setOrigin(25.f,31.5f);
    this->sprite->setScale(-1.f,1.f);
    this->speed.x = 1;
    this->lookRight = false;
    this->lookLeft = true;
    this->animator.playAnimation("walk", true);
}

Zombie::~Zombie() {
    //dtor
}

void Zombie::moveLeft() {
    if(!this->animator.isPlayingAnimation()) {
        this->animator.playAnimation("walk", true);
    }
    this->sprite->setScale(-1.f,1.f);
    this->lookLeft = true;
    this->lookRight = false;
    this->movingRight = false;
    this->movingLeft = true;
    this->sprite->move(-speed.x,speed.y);
    this->attacking = false;
}

void Zombie::moveRight() {
    if(!this->animator.isPlayingAnimation()) {
        this->animator.playAnimation("walk", true);
    }
    this->sprite->setScale(1.f,1.f);
    this->lookLeft = true;
    this->lookRight = false;
    this->movingRight = false;
    this->movingLeft = true;
    this->sprite->move(-speed.x,speed.y);
    this->attacking = false;
}

void Zombie::attack(Player *_player) {
    this->animator.stopAnimation();
    /*this->image_vector.top = 559;
    this->image_vector.width = 84;
    this->image_vector.height = 77;
    this->sprite->setPosition(this->sprite->getPosition().x,this->sprite->getPosition().y - 15);
    if(this->image_vector.left >= 490 || (this->movingLeft && !this->attacking)) {
        this->image_vector.left = 167;
    }
    if(this->image_vector.left >= 167) {
        this->image_vector.left += image_vector.width;
        if(this->image_vector.left >= 503) {
            _player->die();
        }
    }
    this->sprite->setTextureRect(image_vector);*/
    _player->die();
    this->attacking = true;
}

void Zombie::die() {
    this->sprite->setOrigin(77.f,62.f);
    this->animator.playAnimation("die");
    this->movingLeft = false;
    this->attacking = false;
    this->life = false;
}

void Zombie::moveRemain() {
    this->movingLeft = false;
    this->movingRight = false;
}

void Zombie::jump() {
    //The player go the maximum position to jump
    this->jumping = true;
    this->setVelY(-400.f);
}

