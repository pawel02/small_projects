#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.hpp"

struct metaData
{
	const sf::Drawable* drawable;
	char playerWon = 0x00;
};

/*
Spawns a ball (you can spawn as many as you want)
Starts off going in a random direction
onUpdate returns a struct that contains the drawable and metadata
*/
class Ball
{
public:
	Ball(
		const sf::Vector2i& windowSize,
		const int& ballSize,
		const sf::Color& color,
		const float& speed,
		Paddle* paddleLeft,
		Paddle* paddleRight
	) noexcept;
	~Ball() noexcept;


	const metaData& update(float deltaTime) noexcept;

private:
	void initialize() noexcept;

private:
	sf::CircleShape ball;

	Paddle* paddleLeft;
	Paddle* paddleRight;

	sf::Vector2i windowSize;
	int size;
	float speed;
	sf::Color color;

	sf::Vector2f velocity;
};