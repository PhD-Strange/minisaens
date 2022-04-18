#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent {
private:
    Sprite& sprite;
    RectangleShape hitbox;
    float offsetX;
    float offsetY;

public:
    HitboxComponent(Sprite& sprite, float offset_x, float offset_y, float width, float height);
    virtual ~HitboxComponent();

    //Accessors
    const Vector2f& getPosition() const;
    const FloatRect getGlobalBounds() const;

    //Modifiers
    void setPosition(const Vector2f& position);
    void setPosition(const float x, const float y);

    //Functions
    bool intersects(const FloatRect& frect);
    void update();
    void render(RenderTarget& target);
};

#endif