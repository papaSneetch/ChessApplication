#include <iostream>

#ifndef SFML
#include <SFML/Graphics.hpp>
#define SFML
#endif

#include <model.cpp>
#include <control.cpp>

main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    sf::Event event;
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
                    mouse.leftButtonPressed();
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mouse.leftButtonReleased();
                }
                break;
            }
            if (mouse.getIsDragging() && mouse.getObjectToDrag() == &kingPiece)
            {
                kingPiece.dragPiece(mouse.getRecordedPositionf(0), mouse.getDragOffset());
            }
        }
        window.clear();
        mainChessBoard.drawBoard(window);
        kingPiece.drawPiece(window);
        window.display();
    }
    return 0;
}