#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game {
private:
    // Variables
    GraphicsSettings gfxSettings;
    StateData stateData;
    RenderWindow *window;
    Event sfEvent;

    Clock dtClock;
    float dt;
    
    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    float gridSize;

    // Initializer

    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initKeys();
    void initStateData();
    void initStates();

public:
    // Constructors/Destructors
    Game();
    virtual ~Game();

    // Functions

    //Regular

    void endApplication();

    //update
    void updateDt();
    void updateSFMLevents();
    void update();

    //Render
    void render();

    //Core
    void run();

};
#endif