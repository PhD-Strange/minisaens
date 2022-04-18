#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
    void clear();

    float gridSizeF;
    unsigned gridSizeU;
    Vector2u maxSizeWorldGrid;
    Vector2f maxSizeWorldF;
    unsigned layers;
    std::vector<std::vector<std::vector<Tile*>>> map;
    std::string textureFile;
    Texture tileSheet;
    RectangleShape collisionBox;

public:
    TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    virtual ~TileMap();

    //Accessors
    const Texture* getTileSheet() const;

    //Functions
    void addTile(const unsigned x, const unsigned y, const unsigned z, 
        const IntRect& texture_rect, const bool& collision, const short& type);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);

    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);

    void updateCollision(Entity* entity);

    void update();
    void render(RenderTarget& target, Entity* entity = nullptr);
};

#endif