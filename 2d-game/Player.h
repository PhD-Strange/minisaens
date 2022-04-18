#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    //Variables
    bool attacking;

    //Initializer
    void initVariables();
    void initComponents();


public:
    Player(float x, float y, Texture& texture_sheet);
    virtual ~Player();

    // Functions
    void updateAttack();
    void updateAnimation(const float& dt);
    void update(const float& dt);

    void render(RenderTarget& target);
};


#endif