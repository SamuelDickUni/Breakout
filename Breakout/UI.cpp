#include <sstream>

#include "UI.h"
#include "GameManager.h"

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) 
	: _window(window), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);	
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_font.loadFromFile("font/montS.ttf");
}

UI::~UI()
{
}


void UI::updatePowerupText(const std::map<std::shared_ptr<Powerup>, std::vector<float>>& powerups)
{
	while (_powerupTexts.size() < powerups.size())
	{
		_powerupTexts.emplace_back(_window, _font, "", std::vector<float>{});
	}
	int index = 0;
	for (const auto& [powerup, remainingTimes] : powerups)
	{
		if (index < _powerupTexts.size())
		{
			_powerupTexts[index].setVisible(true);
			_powerupTexts[index].updatePowerupName(powerup->getName());
			_powerupTexts[index].updateRemainingTimes(remainingTimes);
			index++;
		}
	}
	for (int i = index; i < _powerupTexts.size(); ++i)
	{
		_powerupTexts[i].setVisible(false);
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	float drawY = 10.f;
	for (auto& powerupText : _powerupTexts)
	{
		powerupText.render(drawY);
	}
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}