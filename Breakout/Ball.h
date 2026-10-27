#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff);
	void setPower(float value);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    float _power = BALL_DEFAULT_DAMAGE;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager
};

