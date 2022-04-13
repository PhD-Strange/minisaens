#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <map>
using namespace sf;

class AnimationComponent {
private:
    class Animation {
    public:
        //Variables
        Sprite& sprite;
        Texture& textureSheet;
        float animationTimer;
        float timer;
        int width;
        int height;
        IntRect startRect;
        IntRect currentRect;
        IntRect endRect;


        Animation(Sprite& sprite, Texture& texture_sheet, float animation_timer, 
        int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
         : sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), width(width), 
        height(height) {
            this->timer = 0.f;
            this->startRect = IntRect(start_frame_x * width, start_frame_y * height, width, height);
            this->currentRect = this->startRect;
            this->endRect = IntRect(frames_x * width, frames_y * height, width, height);

            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(this->startRect);
        }
        ~Animation();

        //Functions
        void play(const float& dt) {
            //update timer
            this->timer += 100.f * dt;
            if (this->timer >= this->animationTimer) {
                // reset timer
                this->timer = 0;

                // Animate
                if (this->currentRect != this->endRect) {
                    this->currentRect.left += this->width;
                }
                else {
                    this->currentRect.left = this->startRect.left;
                }

                this->sprite.setTextureRect(this->currentRect);
            }
        }
        void reset() {
            this->timer = 0.f;
            this->currentRect = this->startRect;
        }
    };
    
    Sprite& sprite;
    Texture& textureSheet;
    std::map<std::string, Animation*> animations;

public:
    AnimationComponent(Sprite& sprite, Texture& texture_sheet);
    virtual ~AnimationComponent();

    // Functions
    void addAnimation(const std::string key, 
        float animation_timer, 
        int start_frame_x, int start_frame_y, int frames_x, int frames_y, 
        int width, int height);

    void play(const std::string key, const float& dt);

    //Functions
};

#endif