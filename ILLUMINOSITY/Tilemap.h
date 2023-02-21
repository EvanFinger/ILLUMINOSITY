#ifndef TILE_MAP
#define TILE_MAP

#include "Tile.h"
#include "Entity.h"
#include "State.h"

class Tilemap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	sf::Vector2u mapSize;
	unsigned short layers;
	std::vector< std::vector < std::vector < Tile* > > > map;
	sf::Texture tileTexture;

	//CULL
	unsigned startX, endX, startY, endY, layer;
public:
	Tilemap(const unsigned gridSizeU);
	virtual ~Tilemap();

	const sf::Vector2u& getmapSize() const;

	void update(Entity* entity, StateData* state_data);
	bool render(sf::RenderTarget& target, Entity* entity, StateData* state_data);
};

#endif