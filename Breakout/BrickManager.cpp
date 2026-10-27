#include "BrickManager.h"
#include "GameManager.h"

BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
}

void BrickManager::createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    float leftEdge;
    if (cols % 2 == 0) 
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight, BRICK_HEALTH);
        }
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        brick.render(*_window);
    }
}



CollisionResponse BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction, Brick*& hitBrick)
{
    CollisionResponse collisionResponse = NoCollision;
    for (Brick& brick : _bricks) {
		if (brick.isDestroyed()) continue; // Skip destroyed bricks
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        sf::FloatRect brickBounds = brick.getBounds();
		float  ballX = ballPosition.x + 0.5f * ball.getGlobalBounds().width;
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
		float left = brickBounds.left;
		float right = brickBounds.left + brickBounds.width;
		float centreX = brickBounds.left + 0.5f * brickBounds.width;
		float top = brickBounds.top;
		float bottom = brickBounds.top + brickBounds.height;
		float centreY = brickBounds.top + 0.5f * brickBounds.height;
		float width = brickBounds.width;
		float height = brickBounds.height;

		float dx = ballX - centreX;
		float dy = ballY - centreY;

		if (std::abs(dx) / width > std::abs(dy) / height)	// horizontal collision
		{ 
			if (dx < 0) { // left side
				collisionResponse = LeftCollision;
			}
			else { // right side
				collisionResponse = RightCollision;
			}
		}
		else												// vertical collision
		{ 
			if (dy < 0) { // top side
				collisionResponse = TopCollision;
			}
			else { // bottom side
				collisionResponse = BottomCollision;
			}
		}
		hitBrick = &brick; // Store the hit brick
		break;
	}
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}

CollisionResponse BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction) {
	Brick* dummyBrick = nullptr; // Create a dummy brick to hold the hit brick
	return checkCollision(ball, direction, dummyBrick);
}