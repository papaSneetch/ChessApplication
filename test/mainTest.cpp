#ifndef iostream
#include <iostream>
#define iostream
#endif

#ifndef SFML
#include <SFML/Graphics.hpp>
#define SFML
#endif

#include <view.cpp>

main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    sf::Event event;
    chessWidget chessObject(sf::Vector2f(60.0f,60.0f),sf::Vector2f(1.5f,1.5f));
    window.setFramerateLimit(framesPerSecond);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear();
        chessObject.drawChessWidget(window);
        window.display();
    }
    return 0;
}