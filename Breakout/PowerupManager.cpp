#include "PowerupManager.h"
#include <iostream>


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _window(window), _paddle(paddle), _ball(ball), _rng(std::random_device{}())
{
}

PowerupManager::~PowerupManager()
{
    
}

void PowerupManager::update(float dt)
{
	for (auto& renderer : _powerupRenderers)
    {
		renderer->update(dt);
    }

    checkPaddleCollisions();    

	for (auto & powerup : _activePowerups)
	{
		powerup.remainingTime -= dt;
	}

	// Remove expired power-ups
	_activePowerups.erase(
		std::remove_if(_activePowerups.begin(), _activePowerups.end(),
			[](const ActivePowerup& powerup) { return powerup.remainingTime <= 0; }),
		_activePowerups.end());


	PaddleModifier accumulatedPaddleModifier{ 0.f };
	BallModifier accumulatedBallModifier{ 0.f, 0.f, 0.f };

	for (const auto& powerup : _activePowerups)
	{
		accumulatedPaddleModifier = accumulatedPaddleModifier + powerup.powerup->getPaddleModifier();
		accumulatedBallModifier = accumulatedBallModifier + powerup.powerup->getBallModifier();
	}

	_paddle->setWidth(1.0f + accumulatedPaddleModifier.getSizeMultiplier());
	_ball->setVelocity((1.0f + accumulatedBallModifier.getSpeedMultiplier()) * BALL_SPEED);
	_ball->setPower((BALL_DEFAULT_DAMAGE + accumulatedBallModifier.getDamageAddent()) * (1.0f + accumulatedBallModifier.getDamageMultiplier()));
}

void PowerupManager::render()
{
    for (auto& renderer : _powerupRenderers)
    {
        renderer->render();
    }
}

void PowerupManager::spawnPowerup()
{

    std::uniform_real_distribution<float> xDist(
        _window->getSize().x * 0.05f,
        _window->getSize().x * 0.95f
    );
	std::uniform_int_distribution<int> powerupTypeDist(0, _registeredPowerups.size() - 1); // upper bound is inclusive

    float spawnX = xDist(_rng);
	int powerupIndex = powerupTypeDist(_rng);

	auto renderer = std::make_shared<PowerupRenderer>(_window, spawnX, _registeredPowerups[powerupIndex]);
	_powerupRenderers.push_back(renderer);   

}

void PowerupManager::checkPaddleCollisions()
{
	while (!_powerupRenderers.empty()) // loop until a miss occurs, or the end
	{
        auto& renderer = _powerupRenderers.front();
		if (renderer->checkCollisionWithPaddle(_paddle))
		{
			ApplyPowerUp(renderer->getPowerup());
			_powerupRenderers.pop_front();
		}
		else if (renderer->isOffScreen())
		{
			_powerupRenderers.pop_front();
		}
		else
		{
			return; // No collision and not off-screen, exit the loop
		}
	}
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerupRenderers.size();
}

const std::deque<ActivePowerup>& PowerupManager::getPowerupsInEffect() const
{
	return _activePowerups;
}
