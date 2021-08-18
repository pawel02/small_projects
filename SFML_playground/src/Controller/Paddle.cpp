#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>
#include "Paddle.hpp"

Paddle::Paddle(
	const sf::Vector2i& windowSize, 
	const int& startX, 
	const sf::Vector2i& paddleSize,
	EventsManager* eventsManager, 
	const float& speed,
	const sf::Color& color,
	char keyUp,
	char keyDown
	) noexcept
	
	:windowSize{windowSize},
	pos{startX, (windowSize.y / 2) - (paddleSize.y / 2)},
	paddleSize{paddleSize},
	eventsManager{eventsManager},
	speed{speed},
	color{color},
	keyUp{keyUp},
	keyDown{keyDown}
{
	initialize();
}

Paddle::~Paddle() noexcept
{}

void Paddle::initialize() noexcept
{
	// subscribet to keypressed events
	eventsManager->subscribe(sf::Event::KeyPressed, [&](std::shared_ptr<BasicEvent> ev) {
		handlePressed(static_cast<KeyPressedEvent*>(ev.get()));
	});
	eventsManager->subscribe(sf::Event::KeyReleased, [&](std::shared_ptr<BasicEvent> ev) {
		handleReleased(static_cast<KeyReleasedEvent*>(ev.get()));
	});

	// Create the sprite and set its correct position
	if (!texture.create(paddleSize.x, paddleSize.y))
	{
		return;
	}

	const int pixelAmount = paddleSize.x * paddleSize.y * 4;
	std::vector<sf::Uint8> pixels = std::vector<sf::Uint8>(pixelAmount);

	for (size_t i = 0; i < pixelAmount; i+=4)
	{
		pixels[i]     = color.r;
		pixels[i + 1] = color.g;
		pixels[i + 2] = color.b;
		pixels[i + 3] = color.a;
	}
	texture.update(&pixels[0]);

	sprite.setTexture(texture);
	sprite.setPosition(pos);
}

const sf::Drawable& Paddle::update(float deltaTime) noexcept
{
	// move the paddle up or down limiting it to the ceilings
	if (key & keyUp)
	{
		pos.y = std::max(pos.y - (speed * deltaTime), 5.0f);
	}
	else if (key & keyDown)
	{
		pos.y = std::min(pos.y + (speed * deltaTime), windowSize.y - (paddleSize.y + 5.0f));
	}

	sprite.setPosition(pos);
	return sprite;
}

void Paddle::handlePressed(KeyPressedEvent* ev) noexcept
{
	switch(ev->getKeyCode())
	{
		case 22:
		{
			key |= KEY_W;
			break;
		}
		case 18:
		{
			key |= KEY_S;
			break;
		}
		case 73:
		{
			key |= KEY_UP;
			break;
		}
		case 74:
		{
			key |= KEY_DOWN;
			break;
		}
	}
}

void Paddle::handleReleased(KeyReleasedEvent* ev) noexcept
{
	switch (ev->getKeyCode())
	{
		case 22:
		{
			key ^= KEY_W;
			break;
		}
		case 18:
		{
			key ^= KEY_S;
			break;
		}
		case 73:
		{
			key ^= KEY_UP;
			break;
		}
		case 74:
		{
			key ^= KEY_DOWN;
			break;
		}
	}
}
