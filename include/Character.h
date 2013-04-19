#include <SFML/Graphics.hpp>
#include <iostream>
#ifndef CHARACTER_H
#define CHARACTER_H
/*!
 *  \brief     Class of characters
 *  \details   This class is the parent class of the all characters in the game
 *  \author    Ricardo Romero B.
 *  \version   0.1
 *  \date      1/20/2013
 *  \copyright GNU Public License.
 */

class Character {
public:
    Character();
    virtual ~Character();
    sf::Texture texture;
    sf::Sprite sprite;
    sf::IntRect image_vector;
    /*!
    * \brief Put the character in the initial position
    * \details Is virtual because not all the characters start in the same position
    */
    virtual void posInit() {
        this->sprite.setPosition(100.f,680.f);
        this->posX = 100.f;
        this->posY = 680.f;
    };

    /*!
     * \brief Main attack of the characters
     * \details Is virtual because not all the characters attack at the same way
    */
    void attack();

    /*!
     * \brief Function to move the character to right
     * \details Add the position of the variable, flip the sprite to right and move the sprite to right
    */
    void moveRight() {
        this->movingLeft = false;
        this->movingRight = true;
        this->posX += 12;
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

    /*!
     * \brief Function to return movingRight
     * \return Return true if the player is moving right, false if is not
    */
    bool ismovingRight() {
        return movingRight;
    }

    /*!
     * \brief Function to set movingRight true or false
     * \details Function to set movingRight true or false
    */
    void setmovingRight(bool moving) {
        this->movingRight = moving;
    }

    /*!
     * \brief Function to move the character to left
     * \details Subtract the position of the variable, flip the sprite to left and move the sprite to left
    */
    void moveLeft() {
        this->movingRight = false;
        this->movingLeft = true;
        this->posX -= 12;
        this->velX = -12;
        //Will not
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

    /*!
     * \brief Function to return movingLeft
     * \return Return true if the player is moving left, false if is not
    */
    bool ismovingLeft() {
        return movingLeft;
    }

    /*!
     * \brief Function to set movingLeft true or false
     * \details Function to set movingLeft true or false
    */
    void setmovingLeft(bool moving) {
        this->movingLeft = moving;
    }

    /*!
     * \brief Function to remain player
     * \details Will put the sprite on the first frame and set movingLeft and movingRight false
    */
    void moveRemain() {
        this->movingLeft = false;
        this->movingRight = false;
        this->velX = 0;
        this->velY = 0;
        this->image_vector.left = 40;
        this->image_vector.top = 352;
        this->sprite.setTextureRect(image_vector);
        if(posY == 680) {
            this->endJumping = true;
        }

    }

    /*!
     * \brief Return the velocity of coordinate X
     * \return Function to return velX
    */
    float getVelX() {
        return velX;
    }

    void jump() {
        if(!this->jumping) {
            if(posY <= 500) {
                this->jumping = true;
            }
            this->posY -= 10;
            this->velY = -10;
            this->sprite.move(velX,velY);
        }
    }

    void falling() {
        jumping = false;
        this->posY += 5;
        this->velY = 5;
        this->sprite.move(velX,velY);
    }

    bool isJumping() {
        return jumping;
    }

    bool isEndJumping() {
        return endJumping;
    }
    /*sf::Sprite getSprite(){
        return this->sprite;
    }
    sf::Texture getTexture(){
        return this->texture;
    }
    sf::IntRect getImage_vector(){
        return this->image_vector;
    }*/
protected:
private:
    /*!
     * \details life If the characters is living, then true, else will be false
    */

    bool life = true;
    bool movingLeft = false;
    bool movingRight = false;
    bool jumping = false;
    bool endJumping = true;
    float velX = 0;
    float velY = 0;
    float posX = 0;
    float posY = 0;

};

#endif // CHARACTER_H
