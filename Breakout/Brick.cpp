#include "Brick.h"
#include "CONSTANTS.h"

Brick::Brick(float x, float y, float width, float height, float maxHealth)
    : _isDestroyed(false), _maxHealth(maxHealth), _health(maxHealth)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);
}

void Brick::render(sf::RenderWindow& window)
{
	// Update the color based on health (from red (100% health) to yellow (50% health) to green (0% health))
	float healthRatio = _health / _maxHealth;
	if (healthRatio > 0.5f) {
		_shape.setFillColor(sf::Color(255, (int)(255 * (0.5f-healthRatio)*2), 0));
	}
    else {
        _shape.setFillColor(sf::Color((int)(255 * healthRatio*2), 255, 0));
    }
    if (!_isDestroyed) {
        window.draw(_shape);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

void Brick::hit(float damage, bool &overkill)
{
	overkill = false;
	float previousHealth = _health;
	_health -= damage;
	if (_health <= 0) {
		_isDestroyed = true;
		overkill = 
			damage > (_maxHealth * OVERKILL_THRESHOLD) ||		// if the damage exceeds the overkill threshold
			_health < -previousHealth;							// damage exceeds double the remaining health
	}
}

void Brick::hit(float damage)
{
	bool overkill = false;
	hit(damage, overkill);

}