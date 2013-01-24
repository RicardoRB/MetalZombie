#include "../include/Level.h"

Level::Level(char file_music[])
{
    //I create the player and music in the level
    this->player1 = new Player("res/characters/players/player1.png");
    this->music = new sf::Music();
    this->music->openFromFile(file_music);
    this->music->play();
    this->music->setLoop(true);
}

Level::~Level()
{
    delete player1;
    delete music;
}
