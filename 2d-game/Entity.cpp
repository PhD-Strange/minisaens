#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables() {
    this->hitboxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
}

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    delete this->hitboxComponent;
    delete this->movementComponent;
    delete this->animationComponent;
}

void Entity::setTexture(Texture& texture) {
    this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(Sprite& sprite, float offset_x, float offset_y, 
    float width, float height) {
    this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, 
const float deceleration) {
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(Texture& texture_sheet) {
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//Accessors
const Vector2f& Entity::getPosition() const {
    if (this->hitboxComponent)
        return this->hitboxComponent->getPosition();

    return this->sprite.getPosition();
}

const FloatRect Entity::getGlobalBounds() const {
    if (this->hitboxComponent)
        return this->hitboxComponent->getGlobalBounds();

    return this->sprite.getGlobalBounds();
}

//Modifiers
void Entity::setPosition(const float x, const float y) {
    if (this->hitboxComponent)
        this->hitboxComponent->setPosition(x, y);
    else
        this->sprite.setPosition(x, y);
}

// Functions
void Entity::move(const float dir_x, const float dir_y, const float& dt) {
    if (this->movementComponent)
        this->movementComponent->move(dir_x, dir_y, dt);
}

void Entity::update(const float& dt) {
    if (this->movementComponent)
        this->movementComponent->update(dt);
}

void Entity::render(RenderTarget& target) {
    
}