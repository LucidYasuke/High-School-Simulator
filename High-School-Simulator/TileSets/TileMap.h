#ifndef TILEMAP_H
#define TILEMAP_H

#include "../Includes.h"

// Taken From sfml-dev.org/tutorials/2.4/graphics-vertex-array.php

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    float width;
    float height;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, sf::Vector2f scale);
    
    sf::FloatRect getGlobalBounds();
};

#endif // !TILEMAP_H
