#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "view.hpp"
#include "model.hpp"
#include <SFML/Graphics.hpp>



class mouse
{
    static const unsigned int numberOfPositionsStored = 2;
    static const unsigned int framesTillIsDraggingIsToggled = 7;
    sf::Vector2f mousePositionf[numberOfPositionsStored];
    sf::Vector2i originalChessSquare;
    sf::Vector2i newChessSquare;
    unsigned int framesLeftButtonIsHeld = 0;
    bool isDragging = false;
    chessPiece *objectToDrag;
    sf::Vector2f draggingOffset;
    bool leftButtonIsPressed = false;

public:
    sf::Vector2f getCurrentPositionf(sf::Window &window)
    {
        return sf::Vector2f((float)sf::Mouse::getPosition(window).x,
                            (float)sf::Mouse::getPosition(window).y);
    }

    sf::Vector2f &getRecordedPositionf(int pastPosition)
    {
        return mousePositionf[pastPosition];
    }

    sf::Vector2f getChangeofPosition(sf::Window &window)
    {
        return getRecordedPositionf(0) - getRecordedPositionf(1);
    }

    bool leftButtonPressed(chessWidget &widget)
    {
        leftButtonIsPressed = !leftButtonIsPressed;
        framesLeftButtonIsHeld = 1;
        objectToDrag = widget.chessPieceCollision(getRecordedPositionf(0));
        originalChessSquare = widget.squareColision(objectToDrag -> getPosition());
        return leftButtonIsPressed;
    }

    bool leftButtonReleased(chessWidget &widget, chessModel &model )
    { 
       if (isDragging = true)
       {
            newChessSquare = widget.squareColision(objectToDrag -> getPosition());
       }
        chessModelInformation::chessPosition originalPosition = {originalChessSquare.x,originalChessSquare.y};
        chessModelInformation::chessPosition newPosition = {newChessSquare.x,newChessSquare.y};
        if (model.checkMove(originalPosition,newPosition))
        {
            model.movePiece(originalPosition,newPosition);
            widget.placeChessPieceOnSquareByPointer(objectToDrag,newChessSquare.x,newChessSquare.y);
        }
        else
        {
            widget.placeChessPieceOnSquareByPointer(objectToDrag,originalChessSquare.x,originalChessSquare.y);
        }
        
        leftButtonIsPressed = false;
        isDragging = false;
        objectToDrag = nullptr;
        draggingOffset = sf::Vector2f(0.0f, 0.0f);
        return leftButtonIsPressed;
    }

    int updateMouse(sf::Window &window)
    {
        for (int i = numberOfPositionsStored - 1; i > 0; i--)
        {
            mousePositionf[i] = mousePositionf[i - 1];
        }
        mousePositionf[0] = getCurrentPositionf(window);
        if (leftButtonIsPressed)
        {
            framesLeftButtonIsHeld = framesLeftButtonIsHeld + 1;
            if (framesTillIsDraggingIsToggled <= framesLeftButtonIsHeld)
            {
                isDragging = true;
                if (framesTillIsDraggingIsToggled == framesLeftButtonIsHeld)
                {
                    draggingOffset = mousePositionf[0] - objectToDrag -> getPosition();
                }
            }
        }
        return 0;
    }

    inline bool getIsDragging()
    {
        return isDragging;
    }

    inline sf::Vector2f getDragOffset()
    {
        return draggingOffset;
    }

    chessPiece* getObjectToDrag()
    {
        return objectToDrag;
    }

} mouse;

#endif