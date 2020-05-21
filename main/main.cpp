
#include "view.hpp"
#include "control.hpp"
#include "boardSetter.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

void userPrompt(int &color) //Make sure you look at for the maxColor and minColor in control.hpp before adding colors.
{   
    std::cout << "Select your starting color." << std::endl;
    std::cout << "White: 0" << std::endl;
    std::cout << "Black: 1" << std::endl;
    std::cout << "Color: ";
    std::cin >> color;
    std::cout << std::endl;
}


int main()
{
    int color;
    userPrompt(color);
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess");
    sf::Event event;
    chessWidget chessObjectWidget(sf::Vector2f(125.0f,60.0f),sf::Vector2f(1.5f,1.5f));
    chessModel chessObjectModel;

    if (color == 0)
    {
        whiteGameSetter.setUpGame(&chessObjectWidget,&chessObjectModel);
        mouse.currentColorToMove = color; 
    }
    else if (color == 1)
    {
        blackGameSetter.setUpGame(&chessObjectWidget,&chessObjectModel);
        mouse.currentColorToMove = color; 
    }
    else
    {
        whiteGameSetter.setUpGame(&chessObjectWidget,&chessObjectModel);
        mouse.currentColorToMove = 0;
    }
    
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