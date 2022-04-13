#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
using namespace sf;

class GameState : public State {
private:
    Player* player;

    // Functions

    void initKeybinds();
    void initTextures();
    void initPlayers();

public:
    GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    // Functions

    void endState();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(RenderTarget* target = nullptr);
};


#endif