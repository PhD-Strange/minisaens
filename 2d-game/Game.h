#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

using namespace sf;

class Game {
private:
    // Variables

    RenderWindow *window;
    Event sfEvent;
    std::vector<VideoMode> videoModes;
    ContextSettings windowSettings;
    bool fullscreen;

    Clock dtClock;
    float dt;
    
    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    // Initializer

    void initVariables();
    void initWindow();
    void initStates();
    void initKeys();

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