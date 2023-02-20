#include "stdafx.h"
#include "Tilemap.h"

Tilemap::Tilemap(const unsigned gridSizeU)
{
	this->gridSizeF = gridSizeU;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->mapSize.x = 1000;
	this->mapSize.y = 1000;
	this->layers = 1;

	if (!this->tileTexture.loadFromFile("Images/TileMap/tileset_tile_1.png"))
		std::cout << "ERROR LOADING TILE TEXTURE";

	this->map.resize(this->mapSize.x, std::vector< std::vector <Tile*> >());
	for (size_t x = 0; x < this->mapSize.x; x++)
	{
		for (size_t y = 0; y < this->mapSize.y; y++)
		{
			this->map[x].resize(this->mapSize.y, std::vector< Tile* >());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, &this->tileTexture));
			}
		}
	}
}

Tilemap::~Tilemap()
{
	for (size_t x = 0; x < this->mapSize.x; x++)
	{
		for (size_t y = 0; y < this->mapSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

const sf::Vector2u& Tilemap::getmapSize() const
{
	return this->mapSize;
}

void Tilemap::update(Entity* entity)
{
	//WORLD BOUNDING
	if (entity->getEntityPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getEntityPosition().y);
		entity->stopX();
	}
	else if (entity->getEntityPosition().x + entity->getGlobalBounds().width > static_cast<float>(mapSize.x) * this->gridSizeF)
	{
		entity->setPosition(static_cast<float>(mapSize.x) * this->gridSizeF - entity->getGlobalBounds().width, entity->getEntityPosition().y);
		entity->stopX();
	}
	if (entity->getEntityPosition().y < 0.f)
	{
		entity->setPosition(entity->getEntityPosition().x, 0.f);
		entity->stopY();
	}
	else if (entity->getEntityPosition().y + entity->getGlobalBounds().height > static_cast<float>(mapSize.y) * this->gridSizeF)
	{
		entity->setPosition(entity->getEntityPosition().x, static_cast<float>(mapSize.y) * this->gridSizeF - entity->getGlobalBounds().height);
		entity->stopY();
	}

	//TILES
	this->startX = entity->getGridPosition(this->gridSizeU).x - 2;
	this->endX = entity->getGridPosition(this->gridSizeU).x + 2;
	this->startY = entity->getGridPosition(this->gridSizeU).y - 2;
	this->endY = entity->getGridPosition(this->gridSizeU).y + 2;
	
	

	for (size_t x = startX; x < endX; x++)
	{
		for (size_t y = startY; y < endY; y++)
		{
			
		}
	}
}

void Tilemap::render(sf::RenderTarget& target, Entity* entity, StateData* state_data)
{
	this->startX = entity->getGridPosition(this->gridSizeU).x - state_data->gfxSettings->resolution.width / this->gridSizeU / 2 - 3;
	this->endX = entity->getGridPosition(this->gridSizeU).x + state_data->gfxSettings->resolution.width / this->gridSizeU / 2 + 3;
	this->startY = entity->getGridPosition(this->gridSizeU).y - state_data->gfxSettings->resolution.height / this->gridSizeU / 2 - 3;
	this->endY = entity->getGridPosition(this->gridSizeU).y + state_data->gfxSettings->resolution.height / this->gridSizeU / 2 + 3;

	for (size_t x = startX; x < endX; x++)
	{
		for (size_t y = startY; y < endY; y++)
		{
			for (auto* z : this->map[x][y])
			{
				z->render(target);
			}
		}
	}
	/*for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z)
					z->render(target);
			}
		}
	}*/
}