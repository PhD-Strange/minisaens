#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class SettingsState : public State {
private:
    Texture backgroundTexture;
    RectangleShape background;
    Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDropList*> dropDownLists;

    Text optionText;

    std::vector<VideoMode> modes;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();
    
public:
    SettingsState(StateData* state_data);
    virtual ~SettingsState();

    // accessors

    //functions

    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);
    void renderGui(RenderTarget& target);
    void render(RenderTarget* target = nullptr);
};

#endif