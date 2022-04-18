#ifndef TILE_H
#define TILE_H

enum TileTypes {DEFAULT = 0, DAMAGING};

class Tile {
private:

protected:
    RectangleShape shape;
    bool collision;
    short type;

public:
    Tile();
    Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const Texture& texture, const IntRect& texture_rect, 
        bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    //Functions
    const bool& getCollision() const;
    const Vector2f& getPosition() const;
    const std::string getAsString() const;

    void update();
    void render(RenderTarget& target);
};

#endif