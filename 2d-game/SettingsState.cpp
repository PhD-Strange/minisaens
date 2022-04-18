#include "stdafx.h"
#include "SettingsState.h"

void SettingsState::initVariables() {
    this->modes = VideoMode::getFullscreenModes();
}

void SettingsState::initBackground() {
    this->background.setSize(
        Vector2f(static_cast<float>(this->window->getSize().x), 
        static_cast<float>(this->window->getSize().y))
    );
    if (!this->backgroundTexture.loadFromFile("Resources/images/backgrounds/bg1.jpg")) {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts() {
    if (!this->font.loadFromFile("Fonts/CyrilicOld.TTF")) {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void SettingsState::initKeybinds() {
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

void SettingsState::initGui() {
    this->buttons["BACK"] = new gui::Button(1000, 880, 250, 65, &this->font,
    "Back", 50, Color(100, 100, 100, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20), 
    Color(150, 150, 150, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0));

    this->buttons["APPLY"] = new gui::Button(800, 880, 250, 65, &this->font,
    "Apply", 50, Color(100, 100, 100, 100), Color(250, 250, 250, 250), Color(20, 20, 20, 20), 
    Color(150, 150, 150, 0), Color(250, 250, 250, 0), Color(20, 20, 20, 0));

    std::vector<std::string> modes_str;
    for (auto &i : this->modes) {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }
    this->dropDownLists["RESOLUTION"] = new gui::DropDropList(800, 450, 200, 50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText() {
    this->optionText.setFont(this->font);
    this->optionText.setPosition(Vector2f(100, 450));
    this->optionText.setCharacterSize(30);
    this->optionText.setFillColor(Color(255, 255, 255, 200));

    this->optionText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialising \n\n");
}

SettingsState::SettingsState(StateData* state_data) : State(state_data) {
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initGui();
    this->initText();
}

SettingsState::~SettingsState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
        delete it->second;
    }

    auto it2 = this->dropDownLists.begin();
    for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2) {
        delete it2->second;
    }
}

// accessors

//functions

void SettingsState::updateInput(const float& dt) {
    
}

void SettingsState::updateGui(const float& dt) {
    //Buttons
    for (auto &it : this->buttons) {
        it.second->update(this->mousePosWindow);
    }

    //Quit the game
    if (this->buttons["BACK"]->isPressed()) {
        this->endState();
    }
    // Apply
    if (this->buttons["APPLY"]->isPressed()) {
        // REMOVE LATER
        this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTIONS"]->getActiveElementId()];
        this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, Style::Default);
    }


    // DropDownLists
    for (auto &it : this->dropDownLists) {
        it.second->update(this->mousePosWindow, dt);
    }
}

void SettingsState::update(const float& dt) {
    this->updateMousePositions();
    this->updateInput(dt);

    this->updateGui(dt);
}

void SettingsState::renderGui(RenderTarget& target) {
    for (auto &it : this->buttons) {
        it.second->render(target);
    }
    for (auto &it : this->dropDownLists) {
        it.second->render(target);
    }
}

void SettingsState::render(RenderTarget* target) {
    if (!target)
        target = this->window;


    target->draw(this->background);

    this->renderGui(*target);

    target->draw(this->optionText);

    // REMOVE laters
    Text mouseText;
    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    mouseText.setFont(this->font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << " " << this->mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}