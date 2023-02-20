#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->movementComponent = nullptr;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->durabilityComponent;
}

//Component Funtions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createDurabilityComponent(int max_health, int max_shield, int armor)
{
	this->durabilityComponent = new DurabilityComponent(max_health, max_shield, armor);
}

const HitboxComponent& Entity::getHitbox() const
{
	return *this->hitboxComponent;
}

const sf::Vector2f& Entity::getEntityPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}


//Functions

void Entity::setPosition(const float& x, const float& y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);
	}
}

void Entity::setScale(float x, float y)
{
	this->sprite.setScale(x, y);
}

void Entity::stop()
{
	if (this->movementComponent)
		this->movementComponent->stop();
}

void Entity::stopX()
{
	if (this->movementComponent)
		this->movementComponent->stopX();
}

void Entity::stopY()
{
	if (this->movementComponent)
		this->movementComponent->stopY();
}



void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	if(this->hitboxComponent)
		this->hitboxComponent->render(target);
}
