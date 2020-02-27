#ifndef SFML
#include <SFML/Graphics.hpp>
#define SFML
#endif

class mouse
{
    static const unsigned int numberOfPositionsStored = 2;
    static const unsigned int framesTillIsDraggingIsToggled = 7;
    sf::Vector2f mousePositionf[numberOfPositionsStored];
    unsigned int framesLeftButtonIsHeld = 0;
    bool isDragging = false;
    chesspiece *objectToDrag;
    sf::Vector2f draggingOffset;
    bool leftButtonIsPressed = false;

public:
    sf::Vector2f getCurrentPositionf(sf::Window &window)
    {
        return sf::Vector2f((float)sf::Mouse::getPosition(window).x,
                            (float)sf::Mouse::getPosition(window).y);
    }

    sf::Vector2f getRecordedPositionf(int pastPosition)
    {
        return mousePositionf[pastPosition];
    }

    sf::Vector2f getChangeofPosition(sf::Window &window)
    {
        return getRecordedPositionf(0) - getRecordedPositionf(1);
    }

    bool leftButtonPressed()
    {
        leftButtonIsPressed = !leftButtonIsPressed;
        framesLeftButtonIsHeld = 1;
        if (kingPiece.testBounds(getRecordedPositionf(0)))
        {
            objectToDrag = &kingPiece;
        }
        return leftButtonIsPressed;
    }

    void leftButtonReleased()
    {
        leftButtonIsPressed = false;
        isDragging = false;
        objectToDrag = nullptr;
        draggingOffset = sf::Vector2f(0.0f, 0.0f);
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
                    draggingOffset = mousePositionf[0] - kingPiece.getPosition();
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

    chesspiece* getObjectToDrag()
    {
        return objectToDrag;
    }

} mouse;