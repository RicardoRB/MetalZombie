#include "../include/Level.h"

Level::Level(char file_music[]) {
    //I create the player and music in the level
    this->player1 = new Player("res/images/characters/players/player1.png");
    this->music = new sf::Music();
    this->music->openFromFile(file_music);
    this->music->play();
    this->music->setLoop(true);
    backgroundImage.loadFromFile("res/images/backgrounds/background_level1.png");
    background.setTexture(backgroundImage);
}

Level::~Level() {
    delete player1;
    delete music;
}
