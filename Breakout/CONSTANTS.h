#pragma once

// implemented powerups
enum POWERUPS
{
    bigPaddle,
    smallPaddle,
    fastBall,
    slowBall,
    fireBall,
    none
};

// Window settings
constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;
constexpr const char* WINDOW_TITLE = "Game";

// Paddle settings
constexpr float PADDLE_WIDTH = 150.0f;
constexpr float PADDLE_HEIGHT = 20.0f;
constexpr float PADDLE_SPEED = 300.0f;

// Ball settings
constexpr float BALL_RADIUS = 10.0f;
constexpr float BALL_SPEED = 400.0f;
constexpr float BALL_MIN_SPEED = 100.0f;
constexpr float BALL_DEFAULT_DAMAGE = 1.0f;

// Brick settings
constexpr float BRICK_WIDTH = 75.0f;
constexpr float BRICK_HEIGHT = 20.0f;
constexpr float BRICK_PADDING = 5.0f;
constexpr int BRICK_ROWS = 5;
constexpr int BRICK_COLUMNS = 10;
constexpr int BRICK_HEALTH = 10; // Default health for bricks

constexpr float OVERKILL_THRESHOLD = 0.9f; // Amount of max health that can be exceeded before overkill is triggered

// Power-up settings
constexpr float POWERUP_RADIUS = 15.0f;
constexpr float POWERUP_SPEED = 150.0f;

// UI settings
constexpr float UI_LIFE_RADIUS = 15.0f;
constexpr float UI_LIFE_PADDING = 20.0f;

// Other game settings
constexpr float PAUSE_TIME_BUFFER = 0.5f;
constexpr float POWERUP_FREQUENCY = 7.5f;
constexpr int INITIAL_LIVES = 10;

// Colour Palette
const sf::Color ballEffectsColour = sf::Color(100, 100, 200, 255); // blue-ish?
const sf::Color paddleEffectsColour = sf::Color(255, 250, 205); // lemon chiffon -- very fancy.
const sf::Color extraBallEffectsColour = sf::Color(41, 110, 1); // metallic green


