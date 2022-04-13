#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    //Variables

    //Initializer
    void initVariables();
    void initComponents();


public:
    Player(float x, float y, Texture& texture_sheet);
    virtual ~Player();

    // Functions
    virtual void update(const float& dt);
};


#endif