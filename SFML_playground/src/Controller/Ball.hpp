#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "glm/glm.hpp"


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
	// initializes the ball in the middle of the screen with a random direction
	void initialize() noexcept;

	// normalizes the direction vector
	void normalize() noexcept;

private:
	sf::CircleShape ball;
	sf::Texture texture;

	Paddle* paddleLeft;
	Paddle* paddleRight;

	sf::Vector2i windowSize;
	int size;
	float fullSize;
	float speed;
	sf::Color color;

	glm::vec2 direction;
};