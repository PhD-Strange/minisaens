#include "stdafx.h"
#include "GameState.h"

// Initializer

void GameState::initDeferredRender() {
    this->renderTexture.create(
        this->stateData->gfxSettings->resolution.width, 
        this->stateData->gfxSettings->resolution.height
    );

    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(IntRect(0, 0, 
        this->stateData->gfxSettings->resolution.width, 
        this->stateData->gfxSettings->resolution.height)
    );
}

void GameState::initView() {
    this->view.setSize(
        Vector2f(this->stateData->gfxSettings->resolution.width, 
            this->stateData->gfxSettings->resolution.height)
    );

    this->view.setCenter(
        Vector2f(this->stateData->gfxSettings->resolution.width / 2.f, 
            this->stateData->gfxSettings->resolution.height) / 2.f
    );
}

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

void GameState::initFonts() {
    if (!this->font.loadFromFile("Fonts/CyrilicOld.TTF")) {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void GameState::initTextures() {
    if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/sprites/Player/PLAYER_SHEET.png")) {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
    }        
}

void GameState::initPauseMenu() {
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 550.f, "Quit");
}

void GameState::initPlayers() {
    this->player = new Player(0.f, 0.f, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Resources/tiles/cobble.png");
    this->tileMap->loadFromFile("text.sth");
}

//Constructors
GameState::GameState(StateData* state_data) : State(state_data) {
    this->initDeferredRender();
    this->initView();
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initPlayers();
    this->initTileMap();
}

GameState::~GameState() {
    delete this->pmenu;
    delete this->player;
    delete this->tileMap;
}

//Functions
void GameState::updateView(const float& dt) {
    this->view.setCenter(std::floor(this->player->getPosition().x), std::floor(this->player->getPosition().y));
}

void GameState::updateInput(const float& dt) {
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
        if (!this->paused) {
            this->pauseState();
        }
        else {
            this->unpauseState();
        }
    }
}

void GameState::updatePlayerInput(const float& dt) {
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, dt);
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, dt);
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(0.f, -1.f, dt);
    if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(0.f, 1.f, dt);
}

void GameState::updatePauseMenuButtons() {
    if (this->pmenu->isButtonPressed("QUIT"))
        this->endState();
}

void GameState::updateTileMap(const float& dt) {
    this->tileMap->update();
    this->tileMap->updateCollision(this->player);
}

void GameState::update(const float& dt) {
    this->updateMousePositions(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);
    
    if (!this->paused) {
        this->updateView(dt);
        this->updatePlayerInput(dt);
        this->player->update(dt);
        this->updateTileMap(dt);
    }
    else {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(RenderTarget* target) {
    if (!target)
        target = this->window;

    this->renderTexture.clear();
    
    this->renderTexture.setView(this->view);
    this->tileMap->render(this->renderTexture);
    this->player->render(this->renderTexture);

    if (this->paused) {
        this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->pmenu->render(this->renderTexture);
    }

    //FINAL RENDER
    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
}