#include "stdafx.h"
#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height, Font* font, 
    std::string text, unsigned character_size, 
    Color text_idle_color, Color text_hover_color, Color text_active_color,
    Color idle_color, Color hover_color, Color active_color, 
    Color outline_idle_color, Color outline_hover_color, Color outline_active_color, 
    short unsigned id) {
        this->buttonState = BTN_IDLE;
        this->id = id;

        this->shape.setPosition(Vector2f(x, y));
        this->shape.setSize(Vector2f(width, height));
        this->shape.setFillColor(idle_color);
        this->shape.setOutlineThickness(1.f);
        this->shape.setOutlineColor(outline_idle_color);

        this->font = font;
        this->text.setFont(*this->font);
        this->text.setString(text);
        this->text.setFillColor(text_idle_color);
        this->text.setCharacterSize(character_size);
        this->text.setPosition(
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y
        );

        this->textIdleColor = text_idle_color;
        this->textHoverColor = text_hover_color;
        this->textActiveColor = text_active_color;

        this->idleColor = idle_color;
        this->hoverColor = hover_color;
        this->activeColor = active_color;

        this->outlineIdleColor = outline_idle_color;
        this->outlineHoverColor = outline_hover_color;
        this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button() {

}

// Accessors

const bool gui::Button::isPressed() const {
    if (this->buttonState == BTN_ACTIVE)
        return true;
    
    return false;
}

const std::string gui::Button::getText() const {
    return this->text.getString();
}

const short unsigned& gui::Button::getId() const {
    return this->id;
}

// Modifiers

void gui::Button::setText(const std::string text) {
    this->text.setString(text);
}

void gui::Button::setId(const short unsigned id) {
    this->id = id;
}

// Functions
void gui::Button::update(const Vector2i& mousePosWindow) {
    /*Update the booleans for hover and pressed*/

    this->buttonState = BTN_IDLE;

    //Hover
    if (this->shape.getGlobalBounds().contains(static_cast<Vector2f>(mousePosWindow))) {
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
        this->shape.setOutlineColor(this->outlineIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        this->shape.setOutlineColor(this->outlineHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        this->shape.setOutlineColor(this->outlineActiveColor);
        break;
    default:
        this->shape.setFillColor(Color::Red);
        this->text.setFillColor(Color::Blue);
        this->shape.setOutlineColor(Color::Green);
        break;
    }
}

void gui::Button::render(RenderTarget& target) {
    target.draw(this->shape);
    target.draw(this->text);
}

/////////////////// DROP DOWN LIST ////////////////////////////////

gui::DropDropList::DropDropList(float x, float y, float width, float height, Font& font, std::string list[], unsigned nrOfElements, unsigned default_index) : 
    font(font), showList(false), keytimeMax(10.f), keytime(0.f) {
    //unsigned ntOfElements = sizeof(list) / sizeof(std::string);
    this->activeElement = new gui::Button(x, y, width, height, &this->font, list[default_index], 30, 
            Color(255, 255, 255, 150), Color(255, 255, 255, 200), Color(20, 20, 20, 20),
            Color(150, 150, 150, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200), 
            Color(255, 255, 255, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50));

    for (size_t i = 0; i < nrOfElements; i++) {
        this->list.push_back(new gui::Button(x, y + ((i + 1) * height), width, height, &this->font, list[i], 30, 
            Color(255, 255, 255, 150), Color(255, 255, 255, 255), Color(20, 20, 20, 20),
            Color(150, 150, 150, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200), 
            Color(255, 255, 255, 0), Color(255, 255, 255, 0), Color(20, 20, 20, 0), i));
    }
}

gui::DropDropList::~DropDropList() {
    delete this->activeElement;
    for (size_t i = 0; i < this->list.size(); i++) {
        delete this->list[i];
    }
}


//Accessors
const bool gui::DropDropList::getKeytime() {
    if (this->keytime >= this->keytimeMax) {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

const unsigned short& gui::DropDropList::getActiveElementId() const {
    return this->activeElement->getId();
}

//Functions
void gui::DropDropList::updateKeytime(const float& dt) {
    if (this->keytime < this->keytimeMax) {
        this->keytime += 10.f * dt;
    }
}

void gui::DropDropList::update(const Vector2i& mousePosWindow, const float& dt) {
    this->updateKeytime(dt);
    this->activeElement->update(mousePosWindow);

    if (this->activeElement->isPressed() && this->getKeytime()) {
        if (this->showList)
            this->showList = false;
        else
            this->showList = true;
    }

    if (this->showList) {
        for (auto &i : this->list) {
            i->update(mousePosWindow);

            if (i->isPressed() && this->getKeytime()) {
                this->showList = false;
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
            }
        }
    }
}

void gui::DropDropList::render(RenderTarget& target) {
    this->activeElement->render(target);
    if (this->showList) {
        for (auto &i : this->list) {
            i->render(target);
        }
    }
}


/////////////////// TEXTURE SELECTOR ////////////////////////////////

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, 
    float gridSize, const Texture* texture_sheet, Font& font, std::string text) : 
    keytimeMax(1.f), keytime(0.f) {
    this->gridSize = gridSize;
    this->active = false;
    this->hidden = false;
    float offset = 100.f;

    this->bounds.setSize(Vector2f(width, height));
    this->bounds.setPosition(x + offset, y);
    this->bounds.setFillColor(Color(50, 50, 50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(Color(255, 255, 255, 200));

    this->sheet.setTexture(*texture_sheet);
    this->sheet.setPosition(x + offset, y);

    if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width) {
        this->sheet.setTextureRect(IntRect(0, 0, this->bounds.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
    }
    if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height) {
        this->sheet.setTextureRect(IntRect(0, 0, this->bounds.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
    }

    this->selector.setPosition(x + offset, y);
    this->selector.setSize(Vector2f(gridSize, gridSize));
    this->selector.setFillColor(Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(Color::Red);

    this->textureRect.width = static_cast<int>(gridSize);
    this->textureRect.height = static_cast<int>(gridSize);

    this->hide_btn = new gui::Button(x, y, 50, 50, &font, text, 16, 
    Color(255, 255, 255, 200), Color(255, 255, 255, 250), Color(255, 255, 255, 50),
    Color(70, 70, 70, 200), Color(150, 150, 150, 250), Color(20, 20, 20, 50));;
}

gui::TextureSelector::~TextureSelector() {
    delete this->hide_btn;
}

//Accessors
const bool& gui::TextureSelector::getActive() const {
    return this->active;
}

const IntRect& gui::TextureSelector::getTextureRect() const {
    return this->textureRect;
}

const bool gui::TextureSelector::getKeytime() {
    if (this->keytime >= this->keytimeMax) {
        this->keytime = 0.f;
        return true;
    }
    return false;
}

//Functions
void gui::TextureSelector::updateKeytime(const float& dt) {
    if (this->keytime < this->keytimeMax) {
        this->keytime += 10.f * dt;
    }
}

void gui::TextureSelector::update(const Vector2i& mousePosWindow, const float& dt) {
    this->updateKeytime(dt);
    this->hide_btn->update(mousePosWindow);

    if (this->hide_btn->isPressed() && this->getKeytime()) {
        if (this->hidden) {
            this->hidden = false;
        }
        else {
            this->hidden = true;
        }
    }

    if (!this->hidden) {
        if (this->bounds.getGlobalBounds().contains(static_cast<Vector2f>(mousePosWindow))) {
            this->active = true;
        }
        else {
            this->active = false;
        }

        if (this->active) {
            this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
            this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
            
            this->selector.setPosition(
                this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
            );

            //Update texture rectangle
            this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
            this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
        }
    }
}

void gui::TextureSelector::render(RenderTarget& target) {
    if (!this->hidden) {
        target.draw(this->bounds);
        target.draw(this->sheet);

        if (this->active) {
            target.draw(this->selector);
        }
    }

    this->hide_btn->render(target);
}