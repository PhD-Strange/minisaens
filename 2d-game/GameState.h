#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class PauseMenu;
class Player;
class TileMap;

class GameState : public State {
private:
    View view;
    RenderTexture renderTexture;
    Sprite renderSprite;

    Font font;
    PauseMenu* pmenu;

    Player* player;
    Texture texture;

    TileMap* tileMap;


    // Functions
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    // Functions
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void update(const float& dt);
    void render(RenderTarget* target = nullptr);
};


#endif