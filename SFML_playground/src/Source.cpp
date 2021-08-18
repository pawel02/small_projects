#include <iostream>
#include <chrono>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "./EventSystem/KeyboardEvent.hpp"
#include "Controller/Paddle.hpp"

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");
    window.setFramerateLimit(60.0f);

    EventsManager eventManager;
    Paddle paddle{ 
        {windowWidth, windowHeight}, 
        20, 
        {20, 100}, 
        &eventManager, 
        1, 
        {255, 155, 155, 255} };
    
    sf::Clock clock;
    sf::Int32 currTime = clock.getElapsedTime().asMicroseconds();

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
                    eventManager.dispatch(event.type, std::make_shared<KeyPressedEvent>(event.key.code));
                    break;
                }
                case (sf::Event::KeyReleased):
                {
                    eventManager.dispatch(event.type, std::make_shared<KeyReleasedEvent>(event.key.code));
                    break;
                }
                default:
                {
                    eventManager.dispatch(event.type, std::make_shared<BasicEvent>());
                }

            }
        }

        window.clear();

        // calculate deltaTime
        float deltaTime = static_cast<float>(clock.getElapsedTime().asMicroseconds() - currTime) / 1000.0f;
        currTime = clock.getElapsedTime().asMicroseconds();

        window.draw(paddle.update(deltaTime));
        window.display();
    }
    return EXIT_SUCCESS;
}