#include "stdafx.h"
#include "Player.h"

//Initializer
void Player::initVariables() {
    this->attacking = false;
}

void Player::initComponents() {
    
}

//Constructors
Player::Player(float x, float y, Texture& texture_sheet) {
    this->initVariables();
    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 70, 20, 70, 90);
    this->createMovementComponent(300.f, 15.f, 5.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 9, 0, 200, 120);
    this->animationComponent->addAnimation("WALK", 2.f, 0, 1, 9, 1, 200, 120);
    this->animationComponent->addAnimation("ATTACK", 4.f, 0, 2, 9, 2, 200, 120);
}

Player::~Player() {
    
}

void Player::updateAttack() {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        this->attacking = true;
    }
}

void Player::updateAnimation(const float& dt) {
    if (this->attacking) {
        //Set origin depending on direction
        if (this->sprite.getScale().x > 0.f) { //facing left
            this->sprite.setOrigin(20, 0);
        }
        else { // facing right
            this->sprite.setOrigin(210 + 20, 0);
        }
        // Animate and check for animation end
        if (this->animationComponent->play("ATTACK", dt, true)) {
            this->attacking = false;
            if (this->sprite.getScale().x > 0.f) { //facing left
                this->sprite.setOrigin(0, 0);
            }
            else { // facing right
                this->sprite.setOrigin(210, 0);
            }
        }
    }
    if (this->movementComponent->getState(IDLE)) {
        this->animationComponent->play("IDLE", dt);
    }
    else if (this->movementComponent->getState(MOVING_RIGHT)) {
        if (this->sprite.getScale().x < 0.f) {
            this->sprite.setOrigin(0.f, 0.f);
            this->sprite.setScale(1.f, 1.f);
        }
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, 
            this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_LEFT)) {
        if (this->sprite.getScale().x > 0.f) {
                this->sprite.setOrigin(210, 0.f);
                this->sprite.setScale(-1.f, 1.f);
        }
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, 
            this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_UP)) {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, 
            this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_DOWN)) {
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, 
            this->movementComponent->getMaxVelocity());
    }
}

void Player::update(const float& dt) {
    this->movementComponent->update(dt);
    
    this->updateAttack();

    this->updateAnimation(dt);

    this->hitboxComponent->update();
}

void Player::render(RenderTarget& target) {
    target.draw(this->sprite);

    this->hitboxComponent->render(target);
}