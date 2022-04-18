#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState : public State {
private:
    //Variables
    View view;

    Font font;
    Text cursorText;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*> buttons;

    TileMap* tileMap;

    RectangleShape sidebar;

    RectangleShape selectorRect;

    gui::TextureSelector* textureSelector;

    IntRect textureRect;
    bool collision;
    short type;
    float cameraSpeed;

    // Functions
    void initVariables();
    void initView();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initGui();
    void initTileMap();
    
public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    // Functions

    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderButtons(RenderTarget& target);
    void renderGui(RenderTarget& target);
    void render(RenderTarget* target = nullptr);
};


#endif