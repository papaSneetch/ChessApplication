#ifndef SFML
#include <SFML/Graphics.hpp>
#define SFML
#endif

const unsigned int framesPerSecond = 60;

class chessBoard
{
    sf::Sprite sprite;
    sf::Texture texture;

public:
    chessBoard()
    {
        if (!texture.loadFromFile("D:\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\chessBoard.png"))
        {
        }
        sprite.setTexture(texture);
    };
    int drawBoard(sf::RenderWindow &window)
    {
        window.draw(sprite);
        return 0;
    }
} mainChessBoard;

class chesspiece
{
    sf::Sprite sprite;
    sf::Texture texture;

public:
    chesspiece()
    {
        if (!texture.loadFromFile("D:\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\king_black.png"))
        {
        }
        sprite.setTexture(texture);
    };
    int drawPiece(sf::RenderWindow &window)
    {
        window.draw(sprite);
        return 0;
    }
    int dragPiece(sf::Vector2f mousePosition, sf::Vector2f offset)
    {
        sprite.setPosition(mousePosition - offset);
        return 0;
    }

    bool testBounds(sf::Vector2f position)
    {
        return sprite.getGlobalBounds().contains(position);
    }

    sf::Vector2f getPosition()
    {
        return sprite.getPosition();
    }

} kingPiece;