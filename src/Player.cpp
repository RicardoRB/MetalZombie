#include "../include/Player.h"
#include <iostream>

Player::Player(char file_texture[], float _windowWidth) {
    sf::Image image;
    if (!image.loadFromFile(file_texture)) {
        //        std::cout << "Error file texture player" << std::endl;
    } else {
        image.createMaskFromColor(sf::Color::Transparent);
        texture->loadFromImage(image);
    }
    //Add walk animation
    for(int i=112; i<433; i=i+64) {
        walk_frames.addFrame(1.f, sf::IntRect(i, 350.f, 54.f, 55.f));
    }
    this->animator.addAnimation("walk", walk_frames, sf::seconds(1.f));

    //Add die animation
    die_frames.addFrame(1.f, sf::IntRect(1072.f, 232.f, 56.f, 24.f));
    this->animator.addAnimation("die", die_frames, sf::seconds(1.f));

    //Add remain animation
    remain_frames.addFrame(1.f, sf::IntRect(40.f, 352.f, 52.f, 54.f));
    this->animator.addAnimation("remain", remain_frames, sf::seconds(1.f));

    this->lives = 3;
    this->sprite->setTexture(*texture);
    this->sprite->setTextureRect(sf::IntRect(0, 0, 0, 0));
    this->sprite->setOrigin(27.f,26.f);
    this->sprite->setScale(-1.f,1.f);
    this->attacking = false;
    this->lookRight = true;
    this->lookLeft = false;
    this->movingLeft = false;
    this->movingRight = false;
    this->endJumping = false;
    this->falling = true;
    this->life = true;
    this->windowWidth = _windowWidth;

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
    if(this->posWindowX <= (this->windowWidth/2)) {
        this->setVelX(120.f);
    } else {
        //Will move the player until the end of the picture
        //when the player arrive at the end of the picture, will move normal
        if(this->sprite->getPosition().x <= 9728) {
            this->sprite->move(3.f,0);
            this->camera.move(3.f,0);
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
    if(this->posWindowX >= 50.f) {
        this->setVelX(-120.f);
    }

}

void Player::attack() {
    this->attacking = true;
    this->shot->playShot();
    this->shot->getSprite()->setPosition(this->sprite->getPosition().x,this->sprite->getPosition().y);
}

void Player::die() {
    if(this->bufferDie.loadFromFile((char*)"res/sounds/effects/characters/players/death.wav")) {
        this->soundDie.setBuffer(this->bufferDie);
        this->soundDie.play();
    }
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
    this->falling = false;
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

float Player::getPosWindowX(sf::RenderWindow *_window) {
    sf::Vector2i worldPos = _window->mapCoordsToPixel(this->getSprite()->getPosition());
    this->posWindowX = worldPos.x;
    return this->posWindowX;
}
