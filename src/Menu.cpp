#include "../include/Menu.h"

Menu::Menu() {
    this->option = 0;
    if (!this->font.loadFromFile("res/fonts/BrushRunes.otf")) {
        //error
    } else {
        this->titleText = sf::Text("MetalZombie",font,100U);
        this->titleText.setColor(sf::Color::Red);
        this->titleText.setPosition(376.f,55.f);
        this->startText = sf::Text("Start Game",font, 80U);
        this->startText.setColor(sf::Color::Red);
        this->startText.setPosition(376.f,400.f);
        this->exitText = sf::Text("Exit",font, 80U);
        this->exitText.setColor(sf::Color::Red);
        this->exitText.setPosition(376.f,500.f);

    }
    this->optionIcon = new Object((char*)"res/images/menu/option_icon.png");
    this->optionIcon->getSpriteObject()->setPosition(320.f,430.f);

    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
    if(this->bufferEffect->loadFromFile((char*)"res/sounds/effects/menu/intro.ogg")) {
        this->soundEffect->setBuffer(*this->bufferEffect);
        this->soundEffect->play();
    }
    this->music = new sf::Music();
    if(!music->openFromFile((char*)"res/sounds/music/menu.ogg")) {
//        std::cout << "Error music in level" << std::endl;
    } else {
        this->music->play();
        this->music->setLoop(true);
    }

}

Menu::~Menu() {
    //dtor
    delete music;
    delete optionIcon;
    delete bufferEffect;
    delete soundEffect;
}

sf::Text Menu::getTextTitle() {
    return this->titleText;
}

sf::Text Menu::getTextStart() {
    return this->startText;
}

sf::Text Menu::getTextExit() {
    return this->exitText;
}

Object* Menu::getOptionIcon() {
    return this->optionIcon;
}

int Menu::getOption() {
    return this->option;
}

void Menu::setOption(int _option) {
    this->option = _option;
}

void Menu::playSelect() {
    delete bufferEffect;
    delete soundEffect;
    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
    if(this->bufferEffect->loadFromFile((char*)"res/sounds/effects/menu/select.ogg")) {
        this->soundEffect->setBuffer(*this->bufferEffect);
        this->soundEffect->play();
    }
}

void Menu::playStart() {
    delete bufferEffect;
    delete soundEffect;
    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
    if(this->bufferEffect->loadFromFile((char*)"res/sounds/effects/menu/start.ogg")) {
        this->soundEffect->setBuffer(*this->bufferEffect);
        this->soundEffect->play();
    }
}
