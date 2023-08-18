#include "stdafx.h"
#include "Tilemap.h"

Tilemap::Tilemap(const unsigned gridSizeU)
{
	this->gridSizeF = static_cast<float>(gridSizeU);
	this->gridSizeU = gridSizeU;
	this->mapSize.x = 10000;
	this->mapSize.y = 10000;
	this->layers = 1;

	this->startX = 0;
	this->startY = 0;
	this->endX = 0;
	this->endY = 0;
	this->layer = 0;

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

void Tilemap::update(Entity* entity, StateData* state_data)
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
	int temp;
	temp = entity->getGridPosition(this->gridSizeU).x - state_data->gfxSettings->resolution.width / this->gridSizeU / 2 - 1;
	if (temp < 1) this->startX = 0;
	else if (temp >= (short)this->mapSize.x) this->startX = this->mapSize.x;
	else this->startX = temp;

	temp = entity->getGridPosition(this->gridSizeU).x + state_data->gfxSettings->resolution.width / this->gridSizeU / 2 + 3;
	if (temp < 1) this->endX = 0;
	else if (temp >= (short)this->mapSize.x) this->endX = this->mapSize.x;
	else this->endX = temp;

	temp = entity->getGridPosition(this->gridSizeU).y - state_data->gfxSettings->resolution.height / this->gridSizeU / 2 - 1;
	if (temp < 1) this->startY = 0;
	else if (temp >= (short)this->mapSize.y) this->startY = this->mapSize.y;
	else this->startY = temp;

	temp = entity->getGridPosition(this->gridSizeU).y + state_data->gfxSettings->resolution.height / this->gridSizeU / 2 + 3;
	if (temp < 1) this->endY = 0;
	else if (temp >= (short)this->mapSize.y) this->endY = this->mapSize.y;
	else this->endY = temp;

	/*for (size_t x = startX; x < endX; x++)
	{
		for (size_t y = startY; y < endY; y++)
		{
			
		}
	}*/
}

bool Tilemap::render(sf::RenderTarget& target, Entity* entity, StateData* state_data)
{
	int temp; bool edge = false;
	temp = entity->getGridPosition(this->gridSizeU).x - state_data->gfxSettings->resolution.width / this->gridSizeU / 2 - 1;
	if (temp < 1) { this->startX = 0; edge = true; }
	else if (temp >= (short)this->mapSize.x) this->startX = this->mapSize.x;
	else this->startX = temp;

	temp = entity->getGridPosition(this->gridSizeU).x + state_data->gfxSettings->resolution.width / this->gridSizeU / 2 + 3;
	if (temp < 1) this->endX = 0;
	else if (temp >= (short)this->mapSize.x) this->endX = this->mapSize.x;
	else this->endX = temp;

	temp = entity->getGridPosition(this->gridSizeU).y - state_data->gfxSettings->resolution.height / this->gridSizeU / 2 - 1;
	if (temp < 1) this->startY = 0;
	else if (temp >= (short)this->mapSize.y) this->startY = this->mapSize.y;
	else this->startY = temp;

	temp = entity->getGridPosition(this->gridSizeU).y + state_data->gfxSettings->resolution.height / this->gridSizeU / 2 + 3;
	if (temp < 1) this->endY = 0;
	else if (temp >= (short)this->mapSize.y) this->endY = this->mapSize.y;
	else this->endY = temp;

	
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

	return edge;
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