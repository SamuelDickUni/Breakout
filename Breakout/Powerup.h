#pragma once
#include <string>


class PaddleModifier
{
	float _sizeMultiplier = 0.f;    // multiplier for paddle size (stacks additively)

public:
	PaddleModifier(float sizeMultiplier = 0.f) : _sizeMultiplier(sizeMultiplier) {}

	float getSizeMultiplier() const { return _sizeMultiplier; }

	PaddleModifier operator +(const PaddleModifier& rhs) const{
		PaddleModifier result;
		result._sizeMultiplier = _sizeMultiplier + rhs._sizeMultiplier;			
		return result;
	}
};
class BallModifier
{
	float _speedMultiplier = 0.f;     // multiplier for ball speed
	float _damageAddent = 0.f;        // additive damage to ball      (applies before multiplier)
	float _damageMultiplier = 0.f;    // multiplier for ball damage   (applies after additive, stacks additively)

public:
	BallModifier(float speedMultiplier = 0.f, float damageAddent = 0.f, float damageMultiplier = 0.f)
		: _speedMultiplier(speedMultiplier), _damageAddent(damageAddent), _damageMultiplier(damageMultiplier) {
	}

	float getSpeedMultiplier() const { return _speedMultiplier; }
	float getDamageAddent() const { return _damageAddent; }
	float getDamageMultiplier() const { return _damageMultiplier; }

	BallModifier operator +(const BallModifier& rhs) const {
		BallModifier result;
		result._speedMultiplier = _speedMultiplier + rhs._speedMultiplier;
		result._damageAddent = _damageAddent + rhs._damageAddent;
		result._damageMultiplier = _damageMultiplier + rhs._damageMultiplier; // multipiers stack additively
		return result;
	}
};

class Powerup {

	PaddleModifier _paddleModifier;
	BallModifier _ballModifier;
	std::string _name;
	float _duration;


public:
	/// <summary>
	/// Initializes a Powerup with a duration, display name, and gameplay modifiers.
	/// </summary>
	/// <param name="duration">The length of time, in seconds, that the power-up effect lasts.</param>
	/// <param name="name">The name of the power-up.</param>
	/// <param name="paddleModifier">The modifier to apply to the paddle.</param>
	/// <param name="ballModifier">The modifier to apply to the ball.</param>
	Powerup(float duration, std::string name, PaddleModifier paddleModifier, BallModifier ballModifier)
		: _paddleModifier(paddleModifier), _ballModifier(ballModifier), _duration(duration), _name(name) {
	}
	Powerup() : _duration(0.f), _name("Untitled") {}
	/// <summary>
	/// Initializes a Powerup with a duration, display name, and gameplay modifiers.
	/// </summary>
	/// <param name="duration">The length of time, in seconds, that the power-up effect lasts.</param>
	/// <param name="name">The name of the power-up.</param>
	/// <param name="paddleModifier">The modifier to apply to the paddle.</param>
	Powerup(float duration, std::string name, PaddleModifier paddleModifier)
		: _paddleModifier(paddleModifier), _duration(duration), _name(name) {
	}

	/// <summary>
	/// Initializes a Powerup with a duration, display name, and gameplay modifiers.
	/// </summary>
	/// <param name="duration">The length of time, in seconds, that the power-up effect lasts.</param>
	/// <param name="name">The name of the power-up.</param>
	/// <param name="ballModifier">The modifier to apply to the ball.</param>
	Powerup(float duration, std::string name, BallModifier ballModifier)
		: _ballModifier(ballModifier), _duration(duration), _name(name) {
	}

	float getDuration() const { return _duration; }
	PaddleModifier getPaddleModifier() const { return _paddleModifier; }
	BallModifier getBallModifier() const { return _ballModifier; }
	std::string getName() const { return _name; }

};