#include "../include/Player.h"
#include <iostream>

Player::Player(char file_texture[]) {
    sf::Image image;
    if (!image.loadFromFile(file_texture)) {
        //        std::cout << "Error file texture player" << std::endl;
    } else {
        image.createMaskFromColor(sf::Color::Transparent);
        texture->loadFromImage(image);
    }
    //Add walk animation
    for(int i=112; i<433; i=i+64) {
        walk_frames.addFrame(1.f, sf::IntRect(i, 350, 54, 55));
    }
    this->animator.addAnimation("walk", walk_frames, sf::seconds(1.f));

    //Add die animation
    die_frames.addFrame(1.f, sf::IntRect(1072, 232, 56, 24));
    this->animator.addAnimation("die", die_frames, sf::seconds(1.f));

    //Add remain animation
    remain_frames.addFrame(1.f, sf::IntRect(40, 352, 52, 54));
    this->animator.addAnimation("remain", remain_frames, sf::seconds(1.f));

    this->lives = 3;
    this->sprite->setTexture(*texture);
    this->sprite->setOrigin(26.f,27.f);
    this->sprite->setPosition(100.f,100.f);
    this->sprite->setScale(-1.f,1.f);
    this->attacking = false;
    this->lookRight = true;
    this->lookLeft = false;
    this->endJumping = false;
    this->posWindowX = this->sprite->getPosition().x;
    this->posWindowY = this->sprite->getPosition().y;

    //Shot
    this->shot = new Shot((char*)"res/images/characters/players/player1.png",(char*)"res/sounds/effects/shots/shot.ogg");
}

Player::~Player() {
    //dtor
    delete shot;
}

void Player::moveRight() {
    this->lookLeft = false;
    this->lookRight = true;
    this->movingLeft = false;
    this->movingRight = true;

    if(this->animator.getPlayingAnimation() == "remain") {
        this->animator.playAnimation("walk", true);
    }
    this->sprite->setScale(-1.f,1.f);
    //The background start move when the player will go
    //middle of the window
    if(this->posWindowX <= 512.f) {
        this->setVelX(120.f);
    } else {
        //Will move the player until the end of the picture
        //when the player arrive at the end of the picture, will move normal
        if(this->sprite->getPosition().x <= 9728) {
            this->sprite->move(2.f,0);
            this->camera.move(2.f,0);
        } else {
            //The player will not can go out the window
            if(this->posWindowX <= 960) {
                this->posWindowX += speed.x;
                this->sprite->move(speed.x,speed.y);
            }
        }
    }
}

void Player::moveLeft() {
    this->lookLeft = true;
    this->lookRight = false;
    this->movingRight = false;
    this->movingLeft = true;

    if(this->animator.getPlayingAnimation() == "remain") {
        this->animator.playAnimation("walk", true);
    }
    this->sprite->setScale(1.f,1.f);
    //The player will not can go out the window
    if(this->posWindowX >= 50) {
        this->setVelX(-120.f);
    }
}

void Player::attack() {
    this->attacking = true;
    this->shot->playShot();
    this->shot->getSpriteObject()->setPosition(this->sprite->getPosition().x,this->sprite->getPosition().y);
    this->shot->setPosWindowX(this->shot->getSpriteObject()->getPosition().x);
}

void Player::die() {
    this->animator.playAnimation("die");
    this->sprite->setOrigin(28.f,12.f);
    this->life = false;
    this->lives = this->lives - 1;
}

void Player::moveRemain() {
    this->animator.playAnimation("remain");
    this->sprite->setOrigin(26.f,27.f);
    this->movingLeft = false;
    this->movingRight = false;
}

void Player::jump() {
    //The player go the maximum position to jump
    this->jumping = true;
    this->setVelY(-400.f);
}

Shot* Player::getShot() {
    return this->shot;
}

sf::View Player::getCamera() {
    return this->camera;
}

void Player::setCamera(sf::View _camera) {
    this->camera = _camera;
}

int Player::getLives() {
    return this->lives;
}

float Player::getPosWindowX() {
    return this->posWindowX;
}

void Player::setPosWindowX(float _posWindowX) {
    this->posWindowX = _posWindowX;
}


