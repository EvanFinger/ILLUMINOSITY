#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitRect;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	virtual ~HitboxComponent();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getPositionNxt(sf::Vector2f& entity_velocity);


	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//Functions
	bool collides(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

#endif