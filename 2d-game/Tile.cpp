#include "stdafx.h"
#include "Tile.h"

Tile::Tile() {
    this->collision = false;
    this->type = 0;
}

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const Texture& texture, const IntRect& texture_rect, 
    bool collision, short type) {
    this->shape.setSize(Vector2f(gridSizeF, gridSizeF));
    this->shape.setFillColor(Color::White);
    //this->shape.setOutlineThickness(1.f);
    //this->shape.setOutlineColor(Color::Black);
    this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(texture_rect);

    this->collision = collision;
    this->type = type;
}

Tile::~Tile() {

}

//Functions
const bool& Tile::getCollision() const {
    return this->collision;
}

const Vector2f& Tile::getPosition() const {
    return this->shape.getPosition();
}

const std::string Tile::getAsString() const {
    std::stringstream ss;
    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision << " "<< this->type;

    return ss.str();
}

void Tile::update() {

}

void Tile::render(RenderTarget& target) {
    target.draw(this->shape);
}