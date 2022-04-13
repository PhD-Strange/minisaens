#include "GameState.h"

// Initializer
void GameState::initKeybinds() {
    std::ifstream ifs("config/gamestate_keybinds.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void GameState::initTextures() {
    if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/sprites/Player/test.png")) {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
    }        
}

void GameState::initPlayers() {
    this->player = new Player(50.f, 50.f, this->textures["PLAYER_IDLE"]);
}

//Constructors
GameState::GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states) {
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState() {
   delete this->player;
}

void GameState::endState() {
    std::cout << "Ending GameState!" << "\n";
}

void GameState::updateInput(const float& dt) {
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, dt);
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);
    
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->endState();
}

void GameState::update(const float& dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->player->update(dt);
}

void GameState::render(RenderTarget* target) {
    if (!target)
        target = this->window;
    
    this->player->render(target);
}