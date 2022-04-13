#include "Game.h"
using namespace sf;

// Static functions

// Initializer
void Game::initVariables() {
    this->window = nullptr;
    this->fullscreen = false;
    this->dt = 0.f;
}

void Game::initWindow() {
    std::ifstream ifs("config/window.ini");
    this->videoModes = VideoMode::getFullscreenModes();

    std::string title = "None";
    VideoMode window_bounds = VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
        this->window = new RenderWindow(window_bounds, title, Style::Fullscreen, windowSettings);
    else
        this->window = new RenderWindow(window_bounds, title, Style::Titlebar | Style::Close, windowSettings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
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

void Game::initStates() {
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

// Constructors/Destructors

Game::Game() {
    this->initWindow();
    this->initKeys();
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

    if (!this->states.empty()) {
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