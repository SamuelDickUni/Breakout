#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies
#include <iostream>

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(BALL_RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    
    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * BALL_RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        _sprite.setPosition(0, 300);
        _direction = { 1, 1 };
        _gameManager->loseLife();
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * BALL_RADIUS);
    }

	Brick* hitBrick = nullptr; // Create a dummy brick to hold the hit brick
    // collision with bricks
    CollisionResponse collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction, hitBrick);
	if (collisionResponse != NoCollision && hitBrick != nullptr)
	{
	    bool overkill = false;
	    hitBrick->hit(_power, overkill); // Apply damage to the hit brick
		if (overkill) {
            return;
		}
        // Adjust position to avoid getting stuck inside the brick
		if (collisionResponse & TopCollision)
		{
			_sprite.setPosition(_sprite.getPosition().x, hitBrick->getBounds().top - 2 * BALL_RADIUS);
			_direction.y = -std::abs(_direction.y); // Ensure the ball is moving upwards
		}
		else if (collisionResponse & BottomCollision)
		{
			_sprite.setPosition(_sprite.getPosition().x, hitBrick->getBounds().top + hitBrick->getBounds().height);
			_direction.y = std::abs(_direction.y); // Ensure the ball is moving downwards
		}
        if (collisionResponse & LeftCollision) {
			_sprite.setPosition(hitBrick->getBounds().left - 2 * BALL_RADIUS, _sprite.getPosition().y);
			_direction.x = -std::abs(_direction.x); // Ensure the ball is moving to the left
		}
        else if (collisionResponse & RightCollision) {
            _sprite.setPosition(hitBrick->getBounds().left + hitBrick->getBounds().width, _sprite.getPosition().y);
			_direction.x = std::abs(_direction.x); // Ensure the ball is moving to the right
        }
	}
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::setVelocity(float value)
{
    _velocity = std::max(value, BALL_MIN_SPEED);
}

void Ball::setPower(float value)
{
    _power = value;
}

