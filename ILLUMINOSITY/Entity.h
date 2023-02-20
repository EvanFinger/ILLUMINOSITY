#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "DamageComponent.h"
#include "DurabilityComponent.h"
#include "HitboxComponent.h"

class Entity
{
private:
	void initVariables();

protected:

	sf::Sprite sprite;

	MovementComponent* movementComponent;
	DamageComponent* damageComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

public:
	//Public Components
	DurabilityComponent* durabilityComponent;

	Entity();
	virtual ~Entity();

	//Component Funtions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,float offset_x, float offset_y,float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createDurabilityComponent(int max_health, int max_shield, int armor);

	//access
	virtual const HitboxComponent& getHitbox() const;
	virtual const sf::Vector2f& getEntityPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::Vector2u getGridPosition(const unsigned gridSizeU) const;

	//Mods
	virtual void setPosition(const float& x, const float& y);
	//Functions

	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void setScale(float x, float y);
	virtual void stop();
	virtual void stopX();
	virtual void stopY();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};

#endif