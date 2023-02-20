#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H


class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;


	//Inits

public:
	MovementComponent(sf::Sprite& sprite,
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//access
	const sf::Vector2f& getVelocity() const;

	//Funcs
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};


#endif