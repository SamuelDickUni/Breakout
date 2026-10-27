#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>

class GameManager;

enum CollisionResponse {
	NoCollision = 0,
	LeftCollision = 1,      // collides with left side of brick
	RightCollision = 2,     // collides with right side of brick
	TopCollision = 4,       // collides with top side of brick
	BottomCollision = 8     // collides with bottom side of brick
};

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    CollisionResponse checkCollision(sf::CircleShape& ball, sf::Vector2f& direction, Brick*& hitBrick);
	CollisionResponse checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);
private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;
};


