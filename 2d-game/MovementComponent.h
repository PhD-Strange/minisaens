#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <ctime>
using namespace sf;

class MovementComponent {
private:
    Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;
    Vector2f velocity;

    // Initializers
    
    
public:
    MovementComponent(Sprite& sprite, float maxVelocity, float acceleration, 
    float deceleration);
    virtual ~MovementComponent();

    //Accessors
    const Vector2f& getVelocity() const;

    // Functions
    void move(const float dir_x, const float dir_y, const float& dt);
    void update(const float& dt);
};

#endif