#include "Player.h"

//Initializer
void Player::initVariables() {

}

void Player::initComponents() {
    
}

//Constructors
Player::Player(float x, float y, Texture& texture_sheet) {
    this->initVariables();
    this->setPosition(x, y);
    this->createMovementComponent(300.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 9, 0, 2000, 1200);
}

Player::~Player() {

}

void Player::update(const float& dt) {
    this->movementComponent->update(dt);

    this->animationComponent->play("IDLE_LEFT", dt);
}