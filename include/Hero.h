#ifndef HERO_H
#define HERO_H


class Player : public Character
{
    public:
        Player();
        virtual ~Player();
    protected:
    private:
        void bool jump(){posY++; return true;};
};

#endif // HERO_H
