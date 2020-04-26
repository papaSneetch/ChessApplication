#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

const unsigned int framesPerSecond = 60;

class chessBoard
{
    sf::Sprite sprite;
    sf::Texture texture;
    static const unsigned int pixelsLengthOfIndividualSquare = 39;

public:
    void setSprite(std::string fileName)
    {
       // std::cout << "Loading ChessBoard texture: " << fileName << std::endl;
        if (!texture.loadFromFile(fileName))
        {
            std::cout << "Failed to load ChessBoard texture!" << std::endl;
        }
        sprite.setTexture(texture);
    }

    void setPosition(sf::Vector2f newPosition)
    {
        sprite.setPosition(newPosition);
    }

    void setScale(sf::Vector2f scale)
    {
        sprite.setScale(scale);
    }

    int drawBoard(sf::RenderWindow &window)
    {
        window.draw(sprite);
        return 0;
    }
};

class chessPiece
{
    sf::Sprite sprite;
    sf::Texture texture;

public:

    chessPiece()
    {
    };

    void setSprite(std::string fileName)
    {
       // std::cout << "Loading ChessPiece texture: " << fileName << std::endl;
        if (!texture.loadFromFile(fileName))
        {
            std::cout << "Failed to load ChessPiece texture!" << std::endl;
        }
        sprite.setTexture(texture);
    }

    void setPosition(sf::Vector2f newPosition)
    {
        sprite.setPosition(newPosition);
    }

    void setScale(sf::Vector2f scale)
    {
        sprite.setScale(scale);
    }

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

    void centralizeSpriteOrgin()
    {
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();
        sprite.setOrigin(sf::Vector2f(spriteBounds.width / 2, spriteBounds.height / 2));
    }
};

class chessSquares
{
    sf::RectangleShape squares[8][8]; // row, collumm
    static constexpr float originalSizeOfSquares = 39.0f;

    void createSquares()
    {
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                squares[y][x] = sf::RectangleShape(sf::Vector2f(originalSizeOfSquares, originalSizeOfSquares));
                squares[y][x].setPosition(sf::Vector2f((float)x * originalSizeOfSquares, (float)y * originalSizeOfSquares));
            }
        }
    }

public:
    
    void setPosition(sf::Vector2f newPosition)
    {
        sf::Vector2f scale = squares[0][0].getScale();
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                squares[y][x].setPosition(newPosition + sf::Vector2f((float)x * originalSizeOfSquares * scale.x, (float)y * originalSizeOfSquares * scale.y));
            }
        }
    }

    void setScale(sf::Vector2f scale)
    {
        sf::Vector2f currentPosition = squares[0][0].getPosition();
        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {
                squares[y][x].setScale(scale);
                squares[y][x].setPosition(currentPosition + sf::Vector2f((float)x * originalSizeOfSquares * scale.x, (float)y * originalSizeOfSquares * scale.y));
            }
        }
    }

    sf::Vector2f getSquareCenter(int row, int collumm)
    {
        sf::Vector2f squarePosition = squares[row][collumm].getPosition();
        sf::FloatRect bounds = squares[row][collumm].getGlobalBounds();
        return (squarePosition + sf::Vector2f(bounds.width/2,bounds.height/2));
    }

    sf::Vector2i squareColision(sf::Vector2f position)
    {
        for (int row = 0; row<8; row++)
        {
            for (int collumm = 0; collumm<8; collumm++)
            {
                if (squares[row][collumm].getGlobalBounds().contains(position))
                {
                    return sf::Vector2i(row,collumm);
                }
            }
        }
        return sf::Vector2i(-1,-1);
    }

    chessSquares()
    {
        createSquares();
    }
};

class chessWidget
{
    chessBoard mainChessBoard;
    chessPiece chessPieces[32];
    chessSquares squares;

   

    int loadChessPiecesSprites()
    {
        chessPieces[0].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\king_white.png");
        chessPieces[1].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\queen_white.png");
        chessPieces[2].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\bishop_white.png");
        chessPieces[3].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\bishop_white.png");
        chessPieces[4].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\knight_white.png");
        chessPieces[5].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\knight_white.png");
        chessPieces[6].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\rook_white.png");
        chessPieces[7].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\rook_white.png");
        for (int i = 8; i < 16; i++)
        {
            chessPieces[i].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\pawn_white.png");
        }
        chessPieces[16].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\king_black.png");
        chessPieces[17].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\queen_black.png");
        chessPieces[18].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\bishop_black.png");
        chessPieces[19].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\bishop_black.png");
        chessPieces[20].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\knight_black.png");
        chessPieces[21].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\knight_black.png");
        chessPieces[22].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\rook_black.png");
        chessPieces[23].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\rook_black.png");
        for (int i = 24; i < 32; i++)
        {
            chessPieces[i].setSprite("C:\\Users\\papaSneetch\\\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\pawn_black.png");
        }
        for (int i = 0; i<32; i++)
        {
            chessPieces[i].centralizeSpriteOrgin();
        }
        return 0;
    }

public:

 enum chessPiecesNames
    {
        whiteKing,
        whiteQueen,
        whiteKingBishop,
        whiteQueenBishop,
        whiteKingKnight,
        whiteQueenKnight,
        whiteKingRook,
        whiteQueenRook,
        whiteAPawn,
        whiteBPawn,
        whiteCPawn,
        whiteDPawn,
        whiteEPawn,
        whiteFPawn,
        whiteGPawn,
        whiteHPawn,
        blackKing,
        blackQueen,
        blackKingBishop,
        blackQueenBishop,
        blackKingKnight,
        blackQueenKnight,
        blackKingRook,
        blackQueenRook,
        blackAPawn,
        blackBPawn,
        blackCPawn,
        blackDPawn,
        blackEPawn,
        blackFPawn,
        blackGPawn,
        blackHPawn,
    };
    void placeChessPieceOnSquare(chessPiecesNames chessPiece, int row, int collumm)
    {
        chessPieces[chessPiece].setPosition(squares.getSquareCenter(row, collumm));
    }

    void placeChessPieceOnSquareByPointer(chessPiece* chessPiece, int row, int collumm)
    {
        chessPiece->setPosition(squares.getSquareCenter(row, collumm));
    }

    void resetChessPieces()
    {
        placeChessPieceOnSquare(whiteKing, 7, 4);
        placeChessPieceOnSquare(whiteQueen, 7, 3);
        placeChessPieceOnSquare(whiteKingBishop, 7, 5);
        placeChessPieceOnSquare(whiteQueenBishop, 7, 2);
        placeChessPieceOnSquare(whiteKingKnight, 7, 6);
        placeChessPieceOnSquare(whiteQueenKnight, 7, 1);
        placeChessPieceOnSquare(whiteKingRook, 7, 7);
        placeChessPieceOnSquare(whiteQueenRook, 7, 0);
        placeChessPieceOnSquare(whiteAPawn, 6, 0);
        placeChessPieceOnSquare(whiteBPawn, 6, 1);
        placeChessPieceOnSquare(whiteCPawn, 6, 2);
        placeChessPieceOnSquare(whiteDPawn, 6, 3);
        placeChessPieceOnSquare(whiteEPawn, 6, 4);
        placeChessPieceOnSquare(whiteFPawn, 6, 5);
        placeChessPieceOnSquare(whiteGPawn, 6, 6);
        placeChessPieceOnSquare(whiteHPawn, 6, 7);
        placeChessPieceOnSquare(blackKing, 0, 4);
        placeChessPieceOnSquare(blackQueen, 0, 3);
        placeChessPieceOnSquare(blackKingBishop, 0, 5);
        placeChessPieceOnSquare(blackQueenBishop, 0, 2);
        placeChessPieceOnSquare(blackKingKnight, 0, 6);
        placeChessPieceOnSquare(blackQueenKnight, 0, 1);
        placeChessPieceOnSquare(blackKingRook, 0, 7);
        placeChessPieceOnSquare(blackQueenRook, 0, 0);
        placeChessPieceOnSquare(blackAPawn, 1, 0);
        placeChessPieceOnSquare(blackBPawn, 1, 1);
        placeChessPieceOnSquare(blackCPawn, 1, 2);
        placeChessPieceOnSquare(blackDPawn, 1, 3);
        placeChessPieceOnSquare(blackEPawn, 1, 4);
        placeChessPieceOnSquare(blackFPawn, 1, 5);
        placeChessPieceOnSquare(blackGPawn, 1, 6);
        placeChessPieceOnSquare(blackHPawn, 1, 7);
    }

    void drawChessWidget(sf::RenderWindow &window)
    {
        mainChessBoard.drawBoard(window);
        for (int i = 0; i < 32; i++)
        {
            chessPieces[i].drawPiece(window);
        }
    }

    void setChessWidgetPosition(sf::Vector2f newPosition)
    {
        mainChessBoard.setPosition(newPosition);
        for (int i=0; i<32; i++)
        {
            chessPieces[i].setPosition(newPosition);
        }
        squares.setPosition(newPosition);
    }

    void setChessWidgetScale(sf::Vector2f scale)
    {
        mainChessBoard.setScale(scale);
        for (int i=0; i<32; i++)
        {
            chessPieces[i].setScale(scale);
        }
        squares.setScale(scale);
    }

    chessPiece* chessPieceCollision(sf::Vector2f position)
    {
        for (int i = 0; i< 32; i++)
        {
            if(chessPieces[i].testBounds(position))
            {
                return &chessPieces[i];
            }
        }
        return nullptr;
    }

    sf::Vector2i squareColision(sf::Vector2f position)
    {
        return squares.squareColision(position);
    }

    chessWidget() /*This code will create all the 
    chessPieces we'll need.*/
    {
        mainChessBoard.setSprite("C:\\Users\\papaSneetch\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\chessBoard.png");
        loadChessPiecesSprites();
        resetChessPieces();
    }

    chessWidget(sf::Vector2f startingPosition, sf::Vector2f scale) /*This code will create all the 
    chessPieces we'll need, the chessBoard and places it all in it's starting 
    positions oriented for White. */
    {
        mainChessBoard.setSprite("C:\\Users\\papaSneetch\\User_Colin\\ColinCode\\Projects\\ChessApplication\\Images\\chessBoard.png");
        loadChessPiecesSprites();
        setChessWidgetPosition(startingPosition);
        setChessWidgetScale(scale);
        resetChessPieces();
    }
};

#endif