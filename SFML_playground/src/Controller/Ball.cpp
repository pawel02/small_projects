#include <stdlib.h>
#include <time.h> 
#include <cmath>
#include <numeric>
#include <iostream>
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
	paddleRight{paddleRight},
	ball{ballSize, 60},
	fullSize{size * 2.0f}
{
	initialize();
}

Ball::~Ball() noexcept
{
}

const metaData& Ball::update(float deltaTime) noexcept
{
	// update the ball based on its current velocity
	sf::Vector2f ballPos = {
		ball.getPosition().x + (direction.x * speed * deltaTime),
		ball.getPosition().y + (direction.y * speed * deltaTime)
	};

	// calculate collisions

	// right side
	if (ballPos.x + fullSize >= windowSize.x)
	{
		ballPos.x = windowSize.x - fullSize;
		// recalculate the direction (reflextion on that point)
		direction = glm::normalize(glm::reflect(glm::normalize(glm::vec2(direction.x, direction.y)), glm::vec2(-1.0f, 0.0f)));
	}

	// bottom
	if (ballPos.y + fullSize >= windowSize.y)
	{
		ballPos.y = windowSize.y - fullSize;
		direction = glm::normalize(glm::reflect(glm::normalize(glm::vec2(direction.x, direction.y)), glm::vec2(0.0f, 1.0f)));
	}

	// left
	if (ballPos.x <= 0.0f)
	{
		ballPos.x = 0.0f;
		direction = glm::normalize(glm::reflect(glm::normalize(glm::vec2(direction.x, direction.y)), glm::vec2(1.0f, 0.0f)));
	}

	// top
	if (ballPos.y <= 0.0f)
	{
		ballPos.y = 0.0f;
		direction = glm::normalize(glm::reflect(glm::normalize(glm::vec2(direction.x, direction.y)), glm::vec2(0.0f, -1.0f)));
	}
	ball.setPosition(ballPos);

	return {
		&ball,
		0x00
	};
}

void Ball::initialize() noexcept
{
	// Create the ball in the middle of the screen
	ball.setFillColor(color);
	ball.setPosition((windowSize.x / 2) - (size / 2), (windowSize.y / 2) - (size / 2));


	// give the ball random velocity
	srand(time(NULL));
	int angle = rand() % 35;
	int isRight = rand() % 2 + 1;
	int isUp = rand() % 2 + 1;
	if (isUp == 2)
	{
		angle = 360 - angle;
	}

	if (isRight == 2)
	{
		angle += 180;
	}
	
	// make sure that the y angle is always small

	direction.x = std::cos(angle * (3.14 / 180));
	direction.y = std::sin(angle * (3.14 / 180));


	direction = glm::normalize(direction);
}