#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include  <string>

class PowerupUIRenderer
{
	std::string _powerupName;
	std::vector<float> _remainingTimes;

	sf::RenderWindow* window;

	sf::Text _powerupText;

	bool _visible = false;

public:
	PowerupUIRenderer(sf::RenderWindow* window, const sf::Font& font, const std::string& powerupName, const std::vector<float>& remainingTimes);
	void render(float& drawY);

	void updatePowerupName(const std::string& powerupName) { _powerupName = powerupName; }
	void updateRemainingTimes(const std::vector<float>& remainingTimes) { _remainingTimes = remainingTimes; }
	void setVisible(bool visible) { _visible = visible; _powerupText.setFillColor(visible ? sf::Color::Cyan : sf::Color::Transparent); }
};