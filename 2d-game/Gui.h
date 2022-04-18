#ifndef GUI_H
#define GUI_H

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};


namespace gui {
    class Button
    {
    private:
        short unsigned buttonState;
        short unsigned id;

        RectangleShape shape;
        Font* font;
        Text text;

        Color textIdleColor;
        Color textHoverColor;
        Color textActiveColor;

        Color idleColor;
        Color hoverColor;
        Color activeColor;

        Color outlineIdleColor;
        Color outlineHoverColor;
        Color outlineActiveColor;

    public:
        Button(float x, float y, float width, float height, Font* font, 
            std::string text, unsigned character_size, 
            Color text_idle_color, Color text_hover_color, Color text_active_color,
            Color idle_color, Color hover_color, Color active_color, 
            Color outline_idle_color = Color::Transparent, Color outline_hover_color = Color::Transparent, Color outline_active_color = Color::Transparent, 
            short unsigned id = 0);
        ~Button();

        // Accessors
        const bool isPressed() const;
        const std::string getText() const;
        const short unsigned& getId() const;

        // Modifiers

        void setText(const std::string text);
        void setId(const short unsigned id);

        //Functions
        void update(const Vector2i& mousePosWindow);
        void render(RenderTarget& target);
    };

    class DropDropList {
    private:
        float keytime;
        float keytimeMax;
        Font& font;
        gui::Button* activeElement;
        std::vector<gui::Button*> list;
        bool showList;

    public:
        DropDropList(float x, float y, float width, float height, Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
        ~DropDropList();

        // Accessors

        const unsigned short& getActiveElementId() const;
        const bool getKeytime();

        //Functions
        void updateKeytime(const float& dt);
        void update(const Vector2i& mousePosWindow, const float& dt);
        void render(RenderTarget& target);
    };


    class TextureSelector {
    private:
        float keytime;
        const float keytimeMax;
        float gridSize;
        bool active;
        bool hidden;
        gui::Button* hide_btn;
        RectangleShape bounds;
        Sprite sheet;
        RectangleShape selector;
        Vector2u mousePosGrid;
        IntRect textureRect;

    public:
        TextureSelector(float x, float y, float width, float height, float gridSize, 
            const Texture* texture_sheet, Font& font, std::string text);
        ~TextureSelector();

        //Accessors
        const bool& getActive() const;
        const IntRect& getTextureRect() const;

        //Functions
        const bool getKeytime();
        void updateKeytime(const float& dt);
        void update(const Vector2i& mousePosWindow, const float& dt);
        void render(RenderTarget& target);
    };
}

#endif
