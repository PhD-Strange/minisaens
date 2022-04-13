#include "MainMenuState.h"

//Initializer

void MainMenuState::initVariables() {
    this->background.setSize(
        Vector2f(static_cast<float>(this->window->getSize().x), 
        static_cast<float>(this->window->getSize().y))
    );
    if (!this->backgroundTexture.loadFromFile("Resources/images/backgrounds/bg1.jpg")) {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initBackground() {

}

void MainMenuState::initFonts() {
    if (!this->font.loadFromFile("Fonts/bukyvedelight.ttf")) {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT bukyvedelight.ttf");
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
    this->buttons["GAME_STATE"] = new Button(840, 480, 250, 50, &this->font, "New Game", 35, 
    Color(150, 150, 150, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20),
    Color(150, 150, 150, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
    this->buttons["SETTINGS"] = new Button(840, 580, 250, 50, &this->font, "Settings", 35, 
    Color(150, 150, 150, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20),
    Color(150, 150, 150, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0));
    this->buttons["EDITOR_STATE"] = new Button(840, 680, 250, 50, &this->font, "Editor", 35, 
    Color(150, 150, 150, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20),
    Color(150, 150, 150, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0));

    this->buttons["EXIT_STATE"] = new Button(840, 880, 250, 50, &this->font,
    "Quit", 35, Color(100, 100, 100, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20), 
    Color(150, 150, 150, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0));
}

MainMenuState::MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states) {
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
        it.second->update(this->mousePosView);
    }

    //Quit the game
    if (this->buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
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

void MainMenuState::renderButtons(RenderTarget* target) {
    for (auto &it : this->buttons) {
        it.second->render(target);
    }
}

void MainMenuState::render(RenderTarget* target) {
    if (!target)
        target = this->window;


    target->draw(this->background);
    this->renderButtons(target);

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