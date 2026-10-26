#include "PowerupRenderer.h"
#include <cmath>
#include <iostream>

PowerupRenderer::PowerupRenderer(sf::RenderWindow* window, float spawnX, std::shared_ptr<Powerup> powerup)
    : _time(0.0f), _powerup(powerup) // Initialize the time variable and powerup
{
    _window = window;
    _sprite.setRadius(RADIUS);
    _isAlive = true;

    // Initial position and direction with some variability
    float initialX = spawnX;
    _sprite.setPosition(initialX, 5);
    _direction = { 0.0f, FLOAT_DOWN_SPEED };

}

PowerupRenderer::~PowerupRenderer()
{
}

void PowerupRenderer::update(float dt)
{
    _time += dt; // Increment time

    // Smooth side-to-side movement using a sine wave
    float sineWave = std::sin(_time * 2.0f); // Adjust the frequency as needed
    _direction.x = sineWave * AMPLITUDE_OF_FALL; // Adjust the amplitude as needed

    // Move the power-up
    _sprite.move(_direction.x * dt, _direction.y * dt);

    //// Smooth color changes
    //for (int i = 0; i < _colours.size(); ++i)
    //{
    //    _colours[i] += 50 * dt; // Increment smoothly over time
    //    if (_colours[i] > 255) _colours[i] -= 255; // Wrap around to stay within valid range
    //}
    //_sprite.setFillColor(sf::Color(static_cast<sf::Uint8>(_colours[0]), static_cast<sf::Uint8>(_colours[1]), static_cast<sf::Uint8>(_colours[2]), 255));

    // Collide with floor (i.e., was missed)
    if (_sprite.getPosition().y + RADIUS * 2 >= _window->getSize().y)
    {
        _isAlive = false;
    }

}

void PowerupRenderer::render()
{
    _window->draw(_sprite);
}

bool PowerupRenderer::checkCollisionWithPaddle(Paddle* paddle)
{
    if (_sprite.getGlobalBounds().intersects(paddle->getBounds()))
    {
        _isAlive = false;
        return true;
    }
    return false;
}
