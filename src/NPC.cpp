#include "../include/NPC.h"

NPC::NPC() {
    //ctor
}

NPC::NPC(char file_texture[]) : Character(file_texture) {
    //ctor
}

NPC::NPC(sf::Texture* _texture) : Character(_texture) {
    //ctor
}

NPC::~NPC() {
    //dtor
    delete sprite;
    delete texture;
}
