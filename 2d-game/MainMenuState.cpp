#include "stdafx.h"
#include "MainMenuState.h"

//Initializer

void MainMenuState::initVariables() {
    
}

void MainMenuState::initBackground() {
    this->background.setSize(
        Vector2f(static_cast<float>(this->window->getSize().x), 
        static_cast<float>(this->window->getSize().y))
    );
    if (!this->backgroundTexture.loadFromFile("Resources/images/backgrounds/bg1.jpg")) {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts() {
    if (!this->font.loadFromFile("Fonts/CyrilicOld.TTF")) {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initKeybinds() {
    std::ifstream ifs("config/mainmenustate_keybinds.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void MainMenuState::initButtons() {
    this->buttons["GAME_NAME"] = new gui::Button(800, 340, 300, 80, &this->font, "Game of Life", 70, 
    Color(250, 0, 0, 250), Color(250, 0, 0, 250), Color(250, 0, 0, 250),
    Color(250, 0, 0, 0), Color(250, 0, 0, 0), Color(250, 0, 0, 0));
    this->buttons["GAME_STATE"] = new gui::Button(840, 480, 250, 65, &this->font, "New Game", 50, 
    Color(150, 150, 150, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20),
    Color(150, 150, 150, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
    this->buttons["SETTINGS_STATE"] = new gui::Button(840, 580, 250, 65, &this->font, "Settings", 50, 
    Color(150, 150, 150, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20),
    Color(150, 150, 150, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0));
    this->buttons["EDITOR_STATE"] = new gui::Button(840, 680, 250, 65, &this->font, "Editor", 50, 
    Color(150, 150, 150, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20),
    Color(150, 150, 150, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0));

    this->buttons["EXIT_STATE"] = new gui::Button(840, 880, 250, 65, &this->font,
    "Quit", 50, Color(100, 100, 100, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20), 
    Color(150, 150, 150, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0));
}

MainMenuState::MainMenuState(StateData* state_data) : State(state_data) {
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }
}

void MainMenuState::updateInput(const float& dt) {
    
}

void MainMenuState::updateButtons() {
    for (auto &it : this->buttons) {
        it.second->update(this->mousePosWindow);
    }

    //Start the game
    if (this->buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->stateData));
    }
    // Settings
    if (this->buttons["SETTINGS_STATE"]->isPressed()) {
        this->states->push(new SettingsState(this->stateData));
    }

    // Editor
    if (this->buttons["EDITOR_STATE"]->isPressed()) {
        this->states->push(new EditorState(this->stateData));
    }

    //Quit the game
    if (this->buttons["EXIT_STATE"]->isPressed()) {
        this->endState();
    }
}

void MainMenuState::update(const float& dt) {
    this->updateMousePositions();
    this->updateInput(dt);

    this->updateButtons();
}

void MainMenuState::renderButtons(RenderTarget& target) {
    for (auto &it : this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::render(RenderTarget* target) {
    if (!target)
        target = this->window;


    target->draw(this->background);
    this->renderButtons(*target);

    /* // REMOVE laters
    Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText); */
}