
#include "view.hpp"
#include "control.hpp"
#include "boardSetter.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    sf::Event event;
    chessWidget chessObjectWidget(sf::Vector2f(100.0f,60.0f),sf::Vector2f(1.0f,1.0f));
    chessModel chessObjectModel;
    whiteGameSetter.setUpGame(&chessObjectWidget,&chessObjectModel);
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
                    mouse.leftButtonPressed(chessObjectWidget);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mouse.leftButtonReleased(chessObjectWidget,chessObjectModel);
                }
                break;
            }
            if (mouse.getIsDragging() && mouse.getObjectToDrag() != nullptr)
            {
                mouse.getObjectToDrag()->dragPiece(mouse.getRecordedPositionf(0), mouse.getDragOffset());
            }
        }
        window.clear();
        chessObjectWidget.drawChessWidget(window);
        window.display();
    }
    return 0;
}