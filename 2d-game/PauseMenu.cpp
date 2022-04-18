#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window, Font& font) : font(font) {
    // Init background
    this->background.setSize(Vector2f(
        static_cast<float>(window.getSize().x), 
        static_cast<float>(window.getSize().y))
    );
    this->background.setFillColor(Color(20, 20, 20, 100));

    // Init container
    this->container.setSize(Vector2f(
        static_cast<float>(window.getSize().x) / 4.f, 
        static_cast<float>(window.getSize().y) - 100.f)
    );
    this->container.setFillColor(Color(20, 20, 20, 200));

    this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - 
    this->container.getSize().x / 2.f, 30.f);

    //Init Text
    this->menuText.setFont(font);
    this->menuText.setFillColor(Color(255, 255, 255, 200));
    this->menuText.setCharacterSize(60);
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f, 
        this->container.getPosition().y + 40
    );
}

PauseMenu::~PauseMenu() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

// accessors

std::map<std::string, gui::Button*>& PauseMenu::getButtons() {
    return this->buttons;
}

//Functions

const bool PauseMenu::isButtonPressed(const std::string key) {
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text) {
    float width = 250; 
    float height = 65;
    float x = this->container.getPosition().x + this->container.getSize().x / 2 - width / 2;
    this->buttons[key] = new gui::Button(x, y, width, height, &this->font, text, 50, 
    Color(150, 150, 150, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20),
    Color(150, 150, 150, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

void PauseMenu::update(const Vector2i& mousePosWindow) {
    for (auto &i : this->buttons) {
        i.second->update(mousePosWindow);
    }
}

void PauseMenu::render(RenderTarget& target) {
    target.draw(this->background);
    target.draw(this->container);

    for (auto& i : this->buttons) {
        i.second->render(target);
    }

    target.draw(this->menuText);
}