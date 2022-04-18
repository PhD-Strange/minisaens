#include "stdafx.h"
#include "Game.h"

// Static functions

// Initializer
void Game::initVariables() {
    this->window = nullptr;
    this->dt = 0.f;
    this->gridSize = 100.f;
}

void Game::initGraphicsSettings() {
    this->gfxSettings.loadFromFile("config/graphics.ini");
}

void Game::initWindow() {
    if (this->gfxSettings.fullscreen)
        this->window = new RenderWindow(this->gfxSettings.resolution, 
        this->gfxSettings.title, Style::Fullscreen, this->gfxSettings.contextSettings);
    else
        this->window = new RenderWindow(this->gfxSettings.resolution, 
        this->gfxSettings.title, Style::Titlebar | Style::Close, this->gfxSettings.contextSettings);
    
    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys() {
    std::ifstream ifs("config/supported_keys.ini");

    if (ifs.is_open()) {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();

    // Debug REMOVE later
    for (auto i : this->supportedKeys) {
        std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initStateData() {
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initStates() {
    this->states.push(new MainMenuState(&this->stateData));
}

// Constructors/Destructors

Game::Game() {
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game() {
    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}


// Functions

void Game::endApplication() {
    std::cout << "Ending Application!" << "\n";
}

void Game::updateDt() {
    /*Updates the dt variable with te time it takes to update and render one frame*/
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLevents() {
    while (this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    this->updateSFMLevents();

    if (!this->states.empty() && this->window->hasFocus()) {
        this->states.top()->update(this->dt);
        if (this->states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }

    // Application end
    else {
        this->endApplication();
        this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    // Render items

    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->updateDt();
        this->update();
        this->render();
    }
}