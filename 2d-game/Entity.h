#ifndef ENTITY_H
#define ENTITY_H

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
    void initVariables();

protected:
    Sprite sprite;

    HitboxComponent* hitboxComponent;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;

public:
    Entity();
    virtual ~Entity();

    // Component Functions
    void setTexture(Texture& texture);
    void createHitboxComponent(Sprite& sprite, float offset_x, float offset_y, 
    float width, float height);
    void createMovementComponent(const float maxVelocity, const float acceleration, 
    const float deceleration); 
    void createAnimationComponent(Texture& texture_sheet);

    //Accessors
    virtual const Vector2f& getPosition() const;
    virtual const FloatRect getGlobalBounds() const;

    //Modifiers
    virtual void setPosition(const float x, const float y);

    // Functions
    virtual void move(const float x, const float y, const float& dt);

    virtual void update(const float& dt) = 0;
    virtual void render(RenderTarget& target) = 0;
};

#endif