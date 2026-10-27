#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true)
{
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
}

Paddle::~Paddle()
{
}

void Paddle::update(float dt)
{
    float position = _sprite.getPosition().x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width)
    {
        _sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        _sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
    }
}

void Paddle::render()
{
    _window->draw(_sprite);
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff)
{
	float _oldWidth = _width;
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    float newX = _sprite.getPosition().x + (_width - _oldWidth) / 2; 
	if (newX < 0) newX = 0; // left bound
	else if (newX + _width > _window->getSize().x) newX = _window->getSize().x - _width; // right bound
    _sprite.setPosition(newX, _sprite.getPosition().y);
}
