#ifndef iostream
#include <iostream>
#define iostream
#endif

#ifndef SFML
#include <SFML/Graphics.hpp>
#define SFML
#endif

#ifndef view
#include <view.cpp>
#define view
#endif

#include <control.cpp>

main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    sf::Event event;
    chessWidget chessObject(sf::Vector2f(100.0f,60.0f),sf::Vector2f(0.5f,0.5f));
    window.setFramerateLimit(framesPerSecond);

    while (window.isOpen())
    {
        mouse.updateMouse(window);
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mouse.leftButtonPressed(chessObject);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mouse.leftButtonReleased();
                }
                break;
            }
            if (mouse.getIsDragging() && mouse.getObjectToDrag() != nullptr)
            {
                mouse.getObjectToDrag()->dragPiece(mouse.getRecordedPositionf(0), mouse.getDragOffset());
            }
        }
        window.clear();
        chessObject.drawChessWidget(window);
        window.display();
    }
    return 0;
}