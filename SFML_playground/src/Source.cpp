#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdio>
#include "./EventSystem/event.hpp"

EventsManager eventManager;


void test(std::shared_ptr<BasicEvent> ev)
{
    printf("Hello world\n");
    eventManager.unsubscribe(sf::Event::KeyPressed, test);
}

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");

    // create a basic sprite
    sf::Texture texture;
    if (!texture.loadFromFile("../res/wood.jpg"))
    {
        printf("Could not load the texture %s", "res/wood.jpg");
        return -1;
    }
    texture.setSmooth(true);
    
    sf::Sprite sprite;
    sprite.setTexture(texture);
    
    const sf::IntRect spriteDimensions = sprite.getTextureRect();
    const int desiredSpriteWidth = 20;
    const int desiredSpriteHeight = 20;

    constexpr int spritePositionX = (windowWidth / 2) - (desiredSpriteWidth / 2);
    constexpr int spritePositionY = (windowHeight / 2) - (desiredSpriteHeight / 2);

    sprite.setScale(1.0f / (static_cast<float>(spriteDimensions.width) / static_cast<float>(desiredSpriteWidth)), 
            1.0f / (static_cast<float>(spriteDimensions.height) / static_cast<float>(desiredSpriteHeight)));
    
    printf("sprite width %f\n", static_cast<double>(sprite.getTextureRect().width) * sprite.getScale().x);
    printf("sprite height %f\n", static_cast<double>(sprite.getTextureRect().height) * sprite.getScale().y);


    sprite.setPosition(spritePositionX, spritePositionY);

    // Allow for moving left and right (This requires a whole event system to capture the user input)
    // Allow jumping behaviour (This requires a whole event system to capture the user input)

    eventManager.subscribe(sf::Event::KeyPressed, test);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            eventManager.dispatch(event.type, std::make_shared<BasicEvent>());
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return EXIT_SUCCESS;
}