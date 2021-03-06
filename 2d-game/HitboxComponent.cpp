#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(Sprite& sprite, float offset_x, float offset_y, 
float width, float height) : sprite(sprite), offsetX(offset_x), offsetY(offset_y) {
    this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
    this->hitbox.setSize(Vector2f(width, height));
    this->hitbox.setFillColor(Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(Color::Green);
}

HitboxComponent::~HitboxComponent() {

}

//Acccessors
const Vector2f& HitboxComponent::getPosition() const {
    return this->hitbox.getPosition();
}

const FloatRect HitboxComponent::getGlobalBounds() const {
    return this->hitbox.getGlobalBounds();
}

//Modifiers
void HitboxComponent::setPosition(const Vector2f& position) {
    this->hitbox.setPosition(position);
    this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitboxComponent::setPosition(const float x, const float y) {
    this->hitbox.setPosition(x, y);
    this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

//Functions
bool HitboxComponent::intersects(const FloatRect& frect) {
    return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update() {
    this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(RenderTarget& target) {
    target.draw(this->hitbox);
}