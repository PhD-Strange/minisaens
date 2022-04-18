#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Gui.h"

class PauseMenu
{
private:
    Font& font;
    Text menuText;
    RectangleShape background;
    RectangleShape container;

    std::map<std::string, gui::Button*> buttons;

    // functions

public:
    PauseMenu(RenderWindow& window, Font& font);
    virtual ~PauseMenu();

    // accessor
    std::map<std::string, gui::Button*>& getButtons(); 

    // functions
    const bool isButtonPressed(const std::string key);
    void addButton(const std::string key, float y, const std::string text);
    void update(const Vector2i& mousePosWindow);
    void render(RenderTarget& target);
};

#endif