#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <optional>
#include <random>
#include "PowerupRenderer.h"
#include "Powerup.h"
#include "Paddle.h"
#include "Ball.h"



struct ActivePowerup
{
	std::shared_ptr<Powerup> powerup;
	float remainingTime;
};

class PowerupManager
{
public:
    PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupManager();

    void update(float dt);
    void render();
    void spawnPowerup(); // Method to spawn a power-up
    void checkPaddleCollisions(); // Check collision with paddle
    int getPowerupsSpawned();
	const std::deque<ActivePowerup> &getPowerupsInEffect() const;

	void ApplyPowerUp(std::shared_ptr<Powerup> powerup)
	{
		_activePowerups.push_back({ powerup, powerup->getDuration() });
	}

	/// <summary>
	/// Registers a list of power-ups by appending them to the internal registered collection.
	/// </summary>
	/// <param name="powerups">An initializer list of shared pointers to Powerup objects to register.</param>
	void RegisterPowerUps(std::initializer_list<std::shared_ptr<Powerup>> powerups)
	{
		_registeredPowerups.insert(_registeredPowerups.end(), powerups.begin(), powerups.end());
	}

private:
    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    std::mt19937 _rng; // mersenne twister

	// powerups that are falling on the screen
	// using a deque as only the bottom-most powerup can be collected first
	std::deque<std::shared_ptr<PowerupRenderer>> _powerupRenderers{}; 

	std::vector<std::shared_ptr<Powerup>> _registeredPowerups{}; // Store registered power-ups
	std::deque<ActivePowerup> _activePowerups{};
};
