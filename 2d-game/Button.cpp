#include "Button.h"

Button::Button(float x, float y, float width, float height, Font* font, 
    std::string text, unsigned character_size, Color text_idle_color, Color text_hover_color, Color text_active_color,
    Color idle_color, Color hover_color, Color active_color) {
        this->buttonState = BTN_IDLE;
        
        this->shape.setPosition(Vector2f(x, y));
        this->shape.setSize(Vector2f(width, height));
        this->shape.setFillColor(idle_color);

        this->font = font;
        this->text.setFont(*this->font);
        this->text.setString(text);
        this->text.setFillColor(text_idle_color);
        this->text.setCharacterSize(character_size);
        this->text.setPosition(
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
        );

        this->textIdleColor = text_idle_color;
        this->textHoverColor = text_hover_color;
        this->textActiveColor = text_active_color;

        this->idleColor = idle_color;
        this->hoverColor = hover_color;
        this->activeColor = active_color;
}

Button::~Button() {

}

// Accessors

const bool Button::isPressed() const {
    if (this->buttonState == BTN_ACTIVE)
        return true;
    
    return false;
}

// Functions



void Button::update(const Vector2f mousePos) {
    /*Update the booleans for hover and pressed*/

    this->buttonState = BTN_IDLE;

    //Hover
    if (this->shape.getGlobalBounds().contains(mousePos)) {
        this->buttonState = BTN_HOVER;

        // Pressed
        if (Mouse::isButtonPressed(Mouse::Left)) {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState) {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        this->text.setFillColor(this->textIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        break;
    default:
        this->shape.setFillColor(Color::Red);
        this->text.setFillColor(Color::Blue);
        break;
    }
}

void Button::render(RenderTarget* target) {
    target->draw(this->shape);
    target->draw(this->text);
}