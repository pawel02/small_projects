#pragma once
#include <SFML/Graphics.hpp>
#include "../EventSystem/KeyboardEvent.hpp"
#include "../common/bit.hpp"

struct PaddleInfo
{
	sf::Vector2f position;
	sf::Vector2i size;
};

/*
Class which defines a paddle that can move up and down at the specified position
*/
class Paddle
{
public:
	Paddle(
		const sf::Vector2i& windowSize,
		const int& startX,
		const sf::Vector2i& paddleSize,
		EventsManager* eventsManager, 
		const float& speed,
		const sf::Color& color,
		sf::Keyboard::Key keyUp,
		sf::Keyboard::Key keyDown) noexcept;

	~Paddle() noexcept;
	
	/*
	Called in the main draw loop
	updates the position of the paddle
	checks for collisions
	*/
	const sf::Drawable& update(float deltaTime) noexcept;

	const PaddleInfo& getPosAndSize() const noexcept;

private:
	void initialize() noexcept;
	void handlePressed(KeyPressedEvent* ev) noexcept;
	void handleReleased(KeyReleasedEvent* ev) noexcept;


private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Color color;

	sf::Vector2i windowSize;
	sf::Vector2f pos;
	sf::Vector2i paddleSize;
	EventsManager* eventsManager;

	float speed = 1.0f;

	char key = 0x00;
	sf::Keyboard::Key keyUp;
	sf::Keyboard::Key keyDown;
};