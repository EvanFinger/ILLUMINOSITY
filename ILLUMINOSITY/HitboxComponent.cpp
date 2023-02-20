#include "stdafx.h"
#include "HitboxComponent.h"


HitboxComponent::HitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;

	this->hitRect.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitRect.setSize(sf::Vector2f(width, height));
	this->hitRect.setFillColor(sf::Color::Transparent);
	this->hitRect.setOutlineThickness(-1.f);
	this->hitRect.setOutlineColor(sf::Color::Green);

}

HitboxComponent::~HitboxComponent()
{

}

//Accessors
const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitRect.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitRect.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::getPositionNxt(sf::Vector2f& entity_velocity)
{
	this->nextPosition.left = this->hitRect.getPosition().x + entity_velocity.x;

	this->nextPosition.top = this->hitRect.getPosition().y + entity_velocity.y;
	return this->nextPosition;
}

//Modifiers
void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitRect.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	this->hitRect.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

//Functions
bool HitboxComponent::collides(const sf::FloatRect& frect)
{
	return this->hitRect.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	this->hitRect.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitRect);
}