#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

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
	const float& getMaxVelocity() const;

	//Funcs
	const bool getState(const short unsigned state) const;
	void stop();
	void stopX();
	void stopY();

	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};


#endif