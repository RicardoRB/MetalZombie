#include "../include/Shot.h"

Shot::Shot() {
    //ctor
}

Shot::Shot(char file_texture[], char file_sound[]) : Object(file_texture) {
    //ctor father
    this->shot_vector.top = 678;
    this->shot_vector.left = 1266;
    this->shot_vector.width = 16;
    this->shot_vector.height = 16;
    this->getSprite()->setTextureRect(this->shot_vector);
    this->path_sound = file_sound;
    this->velX = 10.f;
    this->shot = true;
    this->endShot();
}

Shot::Shot(sf::Texture* _texture, char file_sound[]) : Object(_texture) {
    //ctor father
    this->shot_vector.top = 678;
    this->shot_vector.left = 1266;
    this->shot_vector.width = 16;
    this->shot_vector.height = 16;
    this->getSprite()->setTextureRect(this->shot_vector);
    this->path_sound = file_sound;
    this->velX = 0.f;
    this->shot = true;
    this->endShot();
}

Shot::~Shot() {
    //dtor
    delete path_sound;
    delete sprite;
    delete texture;
}

void Shot::moveShot(bool _right) {
    if(_right) {
        this->velX = 300.f;
    } else {
        this->velX = -300.f;
    }
}

void Shot::endShot() {
    this->setShot(true);
    this->velX = 0.f;
    this->getSprite()->setPosition(-50.f,-50.f);
}

float Shot::getPosWindowX(sf::RenderWindow *_window) {
    sf::Vector2i worldPos = _window->mapCoordsToPixel(this->getSprite()->getPosition());
    this->posWindowX = worldPos.x;
    return this->posWindowX;
}

float Shot::getVelX() {
    return this->velX;
}

bool Shot::isShot() {
    return this->shot;
}

void Shot::setShot(bool _shot) {
    this->shot = _shot;
}

bool Shot::isDirectionRight() {
    return this->directionRight;
}

void Shot::setDirectionRight(bool _direction) {
    this->directionRight = _direction;
}

void Shot::playShot() {
    if(this->bufferShot.loadFromFile(this->path_sound)) {
        this->soundShot.setBuffer(this->bufferShot);
        this->soundShot.play();
    }
}

bool Shot::collisionCharacter(Character *_character) {
    if(_character->isLife() && _character->getSprite()->getGlobalBounds().intersects(this->getSprite()->getGlobalBounds())) {
        return true;
    } else {
        return false;
    }
}
