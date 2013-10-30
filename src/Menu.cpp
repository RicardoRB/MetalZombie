#include "../include/Menu.h"
#include <iostream>

Menu::Menu() {
    this->optionIcon = new Object((char*)"res/images/menu/option_icon.png");
    this->option = 0;
    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
}

Menu::Menu(float windowWidth, float windowHeight) {
    this->option = 0;
    if (!this->font.loadFromFile("res/fonts/BrushRunes.otf")) {
        //error
    } else {
        this->titleText = sf::Text("MetalZombie",font, 100U);
        this->titleText.setColor(sf::Color::Red);
        this->titleText.setPosition((windowWidth/2)-136.f,(((windowHeight/2)/2)/2)-48.f);
        this->startText = sf::Text("Start Game",font, 80U);
        this->startText.setColor(sf::Color::Red);
        this->startText.setPosition((windowWidth/2)-106.5f,(windowHeight/2));
        this->exitText = sf::Text("Exit",font, 80U);
        this->exitText.setColor(sf::Color::Red);
        this->exitText.setPosition((windowWidth/2)-35.5f,(windowHeight/2)+85.f);
    }
    this->introLogo = new Object((char*)"res/images/menu/logo.png");
    this->introLogo->getSprite()->setPosition((windowWidth/2)-(this->introLogo->getSprite()->getGlobalBounds().width/2),(windowHeight/2)-(this->introLogo->getSprite()->getGlobalBounds().height/2));
    this->introLogoCC = new Object((char*)"res/images/menu/logoCC.png");
    this->introLogoCC->getSprite()->setPosition((windowWidth/2)-(this->introLogoCC->getSprite()->getGlobalBounds().width/2),(windowHeight/2)-(this->introLogoCC->getSprite()->getGlobalBounds().height/2));
    this->optionIcon = new Object((char*)"res/images/menu/option_icon.png");
    this->optionIcon->getSprite()->setPosition((windowWidth/2)-200.f,(windowHeight/2)+27.f);

    this->bufferEffect = new sf::SoundBuffer();
    this->soundEffect = new sf::Sound();
    if(this->bufferEffect->loadFromFile((char*)"res/sounds/effects/menu/intro.ogg")) {
        this->soundEffect->setBuffer(*this->bufferEffect);
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
    delete this->music;
    delete this->optionIcon;
    delete this->bufferEffect;
    delete this->soundEffect;
    delete this->introLogo;
}

sf::Text Menu::getTextTitle() {
    return this->titleText;
}

void Menu::setTextTitle(sf::Text text,sf::Color color,sf::Vector2f position) {
    this->titleText = text;
    this->titleText.setColor(color);
    this->titleText.setPosition(position);
}

sf::Text Menu::getTextStart() {
    return this->startText;
}

void Menu::setTextStart(sf::Text text,sf::Color color,sf::Vector2f position) {
    this->startText = text;
    this->startText.setColor(color);
    this->startText.setPosition(position);
}

sf::Text Menu::getTextExit() {
    return this->exitText;
}

void Menu::setTextExit(sf::Text text,sf::Color color,sf::Vector2f position) {
    this->exitText = text;
    this->exitText.setColor(color);
    this->exitText.setPosition(position);
}

Object* Menu::getOptionIcon() {
    return this->optionIcon;
}

Object* Menu::getIntroLogo() {
    return this->introLogo;
}

Object* Menu::getIntroLogoCC() {
    return this->introLogoCC;
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

void Menu::playIntroMenu() {
    this->soundEffect->play();
}
