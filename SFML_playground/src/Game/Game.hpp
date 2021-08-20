#pragma once
#include <iostream>
#include <chrono>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../EventSystem/KeyboardEvent.hpp"
#include "../Controller/Paddle.hpp"
#include "../Controller/Ball.hpp"

/*
Starts the main game loop 
spawns the paddles
Initializes the events manager
*/
class GameManager
{
public:
	GameManager(const sf::Vector2i& windowSize) noexcept;
	~GameManager() noexcept;
	int gameLoop() noexcept;

private:
	void initialize() noexcept;

private:
	sf::RenderWindow window;
	EventsManager eventsManager;

	sf::Clock clock;
	sf::Int32 currTime;

	Paddle paddleLeft;
	Paddle paddleRight;

	Ball ball;
	bool isPlaying = false;
};