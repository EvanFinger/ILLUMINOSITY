#ifndef TILE_MAP
#define TILE_MAP

#include "Tile.h"
#include "Entity.h"

class Tilemap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u mapSize;
	unsigned short layers;
	std::vector< std::vector < std::vector < Tile* > > > map;
	sf::Texture tileTexture;
public:
	Tilemap();
	virtual ~Tilemap();

	void update(Entity* entity);
	void render(sf::RenderTarget& target);
};

#endif