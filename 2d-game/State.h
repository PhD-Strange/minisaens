#ifndef STATE_H
#define STATE_H

#include "Player.h"

using namespace sf;

class State {
private:

protected:
    std::stack<State*>* states;
    RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;

    Vector2i mousePosScreen;
    Vector2i mousePosWindow;
    Vector2f mousePosView;

    //resources
    std::map<std::string, Texture> textures;

    // Functions

    virtual void initKeybinds() = 0;

public:
    State(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();

    const bool& getQuit() const;

    void endState();

    virtual void updateMousePositions();
    virtual void updateInput(const float& dt) = 0;

    virtual void update(const float& dt) = 0;
    virtual void render(RenderTarget* target = nullptr) = 0;
};
#endif