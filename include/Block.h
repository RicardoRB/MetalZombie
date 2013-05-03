#include <SFML/Graphics.hpp>
#ifndef BLOCK_H
#define BLOCK_H

class Block
{
public:
    Block();
    Block(char file_texture[]);
    virtual ~Block();
    sf::Sprite* getBlock();
protected:
private:
    sf::Texture *blockImage = new sf::Texture();
    sf::Sprite *block = new sf::Sprite();
};

#endif // BLOCK_H
