#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

class StateData {
public:
    StateData() {};

    //Variables
    float gridSize;
    RenderWindow* window;
    GraphicsSettings* gfxSettings;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;
};

class State {
private:

protected:
    StateData* stateData;
    std::stack<State*>* states;
    RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;
    float keytime;
    float keytimeMax;
    float gridSize;

    Vector2i mousePosScreen;
    Vector2i mousePosWindow;
    Vector2f mousePosView;
    Vector2u mousePosGrid;

    //resources
    std::map<std::string, Texture> textures;

    // Functions

    virtual void initKeybinds() = 0;

public:
    State(StateData* state_data);
    virtual ~State();

    // Accessors
    const bool& getQuit() const;
    const bool getKeytime();

    //Functions
    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePositions(View* view = nullptr);
    virtual void updateKeytime(const float& dt);
    virtual void updateInput(const float& dt) = 0;

    virtual void update(const float& dt) = 0;
    virtual void render(RenderTarget* target = nullptr) = 0;
};
#endif