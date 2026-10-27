#pragma once
#include <SFML/Graphics.hpp>

class Brick {
    
	float _maxHealth;
	float _health;

public:
    Brick(float x, float y, float width, float height, float maxHealth = 1);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

	bool isDestroyed() const { return _isDestroyed; }

    void hit(float damage, bool &overkill);
	void hit(float damage);

	float getHealth() const { return _health; }

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
};