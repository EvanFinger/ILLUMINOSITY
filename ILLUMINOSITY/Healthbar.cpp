#include "stdafx.h"
#include "Healthbar.h"

void HealthBar::initComponents()
{
	this->durabilityComponent = nullptr;
	this->movementComponent = nullptr;
	this->damageComponent = nullptr;
}

HealthBar::HealthBar(unsigned int max_health, float x, float y, sf::Texture& texture_sheet)
	: heartTextureSheet(texture_sheet)
{
	this->initComponents();

	this->heartTextureSheet = texture_sheet;

	this->maxHealth = max_health;
	this->health = max_health;

	this->setPosition(x, y);

	this->heartInitializationSpacer = 0;

	for (int i = 0; i < this->maxHealth; i++)
	{

		this->hearts[i] = new heart(this->heartInitializationSpacer, 0, this->heartTextureSheet);
		this->heartInitializationSpacer += this->hearts.at(0)->getGlobalBounds().width;
	}
}

HealthBar::~HealthBar()
{
	for (auto iterator : hearts)
	{
		delete iterator.second;
	}
}

void HealthBar::update(const float& dt)
{
	if (this->maxHealth > this->hearts.size())
	{
		for (int i = 0; i < this->maxHealth - this->hearts.size(); i++)
		{
			this->hearts[this->hearts.size()] = new heart(this->heartInitializationSpacer, 0, this->heartTextureSheet);
			this->heartInitializationSpacer += this->hearts.at(0)->getGlobalBounds().width;
		}

	}
	else if (this->maxHealth < this->hearts.size())
	{
		for (int i = 0; i < this->maxHealth - this->hearts.size(); i++)
		{
			this->hearts.erase(this->hearts.size() - 1);
			this->heartInitializationSpacer -= this->hearts.at(0)->getGlobalBounds().width;
		}
	}

	for (int i = 0; i < this->health; i++)
	{
		this->hearts[i]->update(dt);
	}
}

void HealthBar::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->health; i++)
	{
		this->hearts[i]->render(target);
	}
}