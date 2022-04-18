#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Gui.h"

class MainMenuState : public State {
private:
    //Variables
    Texture backgroundTexture;
    RectangleShape background;
    Font font;

    std::map<std::string, gui::Button*> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    
public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    // Functions

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget& target);
    void render(RenderTarget* target = nullptr);
};


#endif