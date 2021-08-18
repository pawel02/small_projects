#include "Ball.hpp"
#include "../common/bit.hpp"

Ball::Ball(
	const sf::Vector2i& windowSize, 
	const int& ballSize, 
	const sf::Color& color, 
	const float& speed,
	Paddle* paddleLeft,
	Paddle* paddleRight) noexcept
	:windowSize{windowSize},
	size{ballSize},
	color{color},
	speed{speed},
	paddleLeft{paddleLeft},
	paddleRight{paddleRight}
{
	initialize();
}

Ball::~Ball() noexcept
{
}

const metaData& Ball::update(float deltaTime) noexcept
{
	//update the ball based on its current velocity

	// TODO: insert return statement here
}

void Ball::initialize() noexcept
{
	// Create the ball in the middle of the screen
	// give the ball random velocity
}
