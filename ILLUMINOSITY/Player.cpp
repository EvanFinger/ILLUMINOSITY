#include "stdafx.h"
#include "Player.h"


//Init Functions
void Player::initVariables()
{
}

void Player::initComponents()
{

}

//Constructors/Destructors
Player::Player(float x, float y, int max_health, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 45.f,50.f, 32.f, 64.f);
	this->createMovementComponent(500.f, 20.f, 10.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("MOVE_RIGHT", 10.f, 0, 0, 11, 0, 64, 64);
	this->animationComponent->addAnimation("MOVE_LEFT", 10.f, 0, 1, 11, 0, 64, 64);

	this->createDurabilityComponent(max_health, 0, 0);

}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->update(dt);
	Entity::update(dt);

	this->hitboxComponent->update();

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("MOVE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("MOVE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("MOVE_RIGHT", dt);
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("MOVE_LEFT", dt);
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("MOVE_RIGHT", dt);
	}
}
