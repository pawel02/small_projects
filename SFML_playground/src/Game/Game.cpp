#include "Game.hpp"

GameManager::GameManager(const sf::Vector2i& windowSize) noexcept
    :window{sf::VideoMode(windowSize.x, windowSize.y), "paddle ball"},
    paddleLeft {
        windowSize,
        20,
        { 20, 100 },
        &eventsManager,
        1,
        { 255, 155, 155, 255 },
        sf::Keyboard::W,
        sf::Keyboard::S
    },
    paddleRight{
        windowSize,
        windowSize.x - 40,
        { 20, 100 },
        &eventsManager,
        1,
        { 45, 45, 155, 255 },
        sf::Keyboard::Up,
        sf::Keyboard::Down
    },
    ball{
    windowSize, 
    10,
        {255, 0, 0},
        0.5f,
        &paddleLeft,
        &paddleRight
    }
{
    initialize();
}

GameManager::~GameManager() noexcept
{}

void GameManager::initialize() noexcept
{
    window.setFramerateLimit(60.0f);
    currTime = clock.getElapsedTime().asMicroseconds();

    // create the ball
}

int GameManager::gameLoop() noexcept
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // send the event to the eventManager
            switch (event.type)
            {
                case (sf::Event::Closed):
                {
                    window.close();
                    break;
                }
                case (sf::Event::KeyPressed):
                {
                    eventsManager.dispatch(event.type, std::make_shared<KeyPressedEvent>(event.key.code));
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        hasGameStarted = true;
                    }
                    break;
                }
                case (sf::Event::KeyReleased):
                {
                    eventsManager.dispatch(event.type, std::make_shared<KeyReleasedEvent>(event.key.code));
                    break;
                }
                default:
                {
                    eventsManager.dispatch(event.type, std::make_shared<BasicEvent>());
                }
            }
        }

        window.clear();

        // calculate deltaTime
        float deltaTime = static_cast<float>(clock.getElapsedTime().asMicroseconds() - currTime) / 1000.0f;
        currTime = clock.getElapsedTime().asMicroseconds();

        window.draw(paddleLeft.update(deltaTime));
        window.draw(paddleRight.update(deltaTime));
        if (hasGameStarted)
            window.draw(*ball.update(deltaTime).drawable);

        window.display();
    }

    return 0;
}