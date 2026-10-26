#include "PowerupUIRenderer.h"
#include <sstream>
#include <iomanip>
#include <iostream>

PowerupUIRenderer::PowerupUIRenderer(sf::RenderWindow* window, const sf::Font& font, const std::string& powerupName, const std::vector<float>& remainingTimes)
	: _powerupName(powerupName), _remainingTimes(remainingTimes), window(window), _powerupText()
{
	// Set up the text properties
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_powerupText.setFont(font);
}

void PowerupUIRenderer::render( float & drawY)
{
	if (!_visible) return;
	int count = _remainingTimes.size();
	std::string text = _powerupName;
	if (count > 1)
	{
		text = std::to_string(count) + " X " + _powerupName;					// <count> X <name>
	}
	_powerupText.setString(text);
	_powerupText.setPosition(800, drawY);
	window->draw(_powerupText);
	drawY += _powerupText.getLocalBounds().height + 5; // Update drawY for the next powerup
}