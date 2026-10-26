#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Powerup.h"





class PowerupRenderer
{
public:
    PowerupRenderer(sf::RenderWindow* window, float spawnX, std::shared_ptr<Powerup> powerup);
    virtual ~PowerupRenderer();

    void update(float dt);
    void render();

    bool checkCollisionWithPaddle(Paddle* paddle);
	bool isOffScreen() const { return _sprite.getPosition().y > _window->getSize().y; }
    std::shared_ptr<Powerup> getPowerup() const { return _powerup; }


protected: // Protected so derived classes can access these members
    // Constants
    static constexpr float RADIUS = 20.f;               // size of powerup on screen
    static constexpr float FLOAT_DOWN_SPEED = 250.0f;   // speed of fall
    static constexpr float AMPLITUDE_OF_FALL = 80.0f;   // waviness of fall

    // Game logic
    float _time;
    bool _isAlive;
    sf::Vector2f _direction;

    // Render
    sf::CircleShape _sprite;
    sf::Color _colour;
    sf::RenderWindow* _window;
	std::shared_ptr<Powerup> _powerup; // Shared pointer to the associated Powerup object

};


