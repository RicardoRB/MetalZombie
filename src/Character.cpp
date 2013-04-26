#include "../include/Character.h"

Character::Character() {
    //ctor
}

Character::~Character() {
    //dtor
}

float Character::getVelX() {
    return velX;
}

float Character::getPosX() {
    return this->sprite.getPosition().x;
}

bool Character::ismovingRight() {
    return movingRight;
}

void Character::setmovingRight(bool moving) {
    this->movingRight = moving;
}

bool Character::ismovingLeft() {
    return movingLeft;
}

void Character::setmovingLeft(bool moving) {
    this->movingLeft = moving;
}

bool Character::isJumping() {
    return jumping;
}

bool Character::isEndJumping() {
    return endJumping;
}

void Character::posInit() {
    this->sprite.setPosition(100.f,680.f);
};

void Character::attack() {

};

void Character::moveRight() {
    this->movingLeft = false;
    this->movingRight = true;
    this->velX = 12;
    if(this->image_vector.left >= 432) {
        this->image_vector.left = 112;
    }
    if(this->image_vector.left >= 112) {
        this->image_vector.left += 52 + 12;
    } else {
        this->image_vector.left = 112;
    }
    this->sprite.setScale(-1.f,1.f);
    this->sprite.setTextureRect(image_vector);
    this->sprite.move(velX,velY);
}

void Character::moveLeft() {
    this->movingRight = false;
    this->movingLeft = true;
    this->velX = -12;
    if(this->image_vector.left >= 432) {
        this->image_vector.left = 112;
    }
    if(this->image_vector.left >= 112) {
        this->image_vector.left += 52 + 12;
    } else {
        this->image_vector.left = 112;
    }
    this->sprite.setScale(1.f,1.f);
    this->sprite.setTextureRect(image_vector);
    this->sprite.move(velX,velY);
}

void Character::moveRemain() {
    this->movingLeft = false;
    this->movingRight = false;
    this->velX = 0;
    this->velY = 0;
    this->image_vector.left = 40;
    this->image_vector.top = 350;
    this->sprite.setTextureRect(image_vector);
}

void Character::jump() {
    if(!this->jumping) {
        if(this->sprite.getPosition().y <= 550.f) {
            this->jumping = true;
            this->velY = 0;
        } else {
            this->velY = -10.f;
        }
        this->sprite.move(velX,velY);
    }
    std::cout << "Jumping " << sprite.getPosition().y << std::endl;
}

void Character::falling() {
    if(sprite.getPosition().y >= 680.f) {
        this->velY = 0;
    } else {
        jumping = false;
        this->velY = 10.f;
    }
    this->sprite.move(velX,velY);
    std::cout<< "Falling "<< sprite.getPosition().y << std::endl;
}
