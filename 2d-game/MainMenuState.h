#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State {
private:
    //Variables
    Texture backgroundTexture;
    RectangleShape background;
    Font font;

    std::map<std::string, Button*> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    
public:
    MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    // Functions

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget* target = nullptr);
    void render(RenderTarget* target = nullptr);
};


#endif