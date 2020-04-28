#include "model.hpp"
#include <iostream>

using namespace chessModelInformation;

enPassantInfo pawnPieceModel::enPassent_Info;

extern nullPieceModel defaultnullPieceModel;

bool chessModel::checkMove(chessPosition originalPosition, chessPosition newPosition)
{
   chessMove move = {originalPosition,newPosition};
   return chessBoard[originalPosition.row][originalPosition.collumm] -> checkMove(move,this->chessBoard);
}

void chessModel::setChessPiece(chessPieceModel* chesspiece, chessPosition position)
{
    chessBoard[position.row][position.collumm] = chesspiece;
}

void chessModel::movePiece(chessPosition originalPosition, chessPosition newPosition)
{
    chessBoard[newPosition.row][newPosition.collumm] = chessBoard[originalPosition.row][originalPosition.collumm];
    chessBoard[originalPosition.row][originalPosition.collumm] = &defaultnullPieceModel;
}

chessModel::chessModel()
{
    chessPosition position;
   for (int row=0; row<8; row++)
    {
        for (int collumm=0; collumm<8; collumm++)
      {
            position.row = row;
            position.collumm = collumm; 
            setChessPiece(&defaultnullPieceModel,position);
       }
    }
}

int chessPieceModel::getPieceColor() const
{
    return pieceColor;
}

bool chessPieceModel::checkMove(const chessMove (&move), chessModelInformation::chessPieceModel *(&chessBoard)[8][8])
{
    std::cout << "Checking move!"<< std::endl;
    std::vector <chessMove> possibleMoves;
    this->getAllPossibleMoves(move.originalPosition,chessBoard,possibleMoves);
    for (int i = 0; i<possibleMoves.size(); i++)
    {
        if ((move.newPosition.collumm == possibleMoves[i].newPosition.collumm) && (move.originalPosition.collumm == possibleMoves[i].originalPosition.collumm) &&
        (move.newPosition.row == possibleMoves[i].newPosition.row) && (move.originalPosition.row == possibleMoves[i].originalPosition.row))
        {
            return true;
        }
    }
    return false;
}

template <std::size_t numberOfCastlingObjects,std::size_t numberOfChessPositionsToCheck>
void kingPieceModel<numberOfCastlingObjects,numberOfChessPositionsToCheck>::getAllPossibleMoves(const chessPosition  position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves))
{
    chessMove newChessMove = {position,position.row+1,position.collumm+1};
    auto conditionalListOfChessMovesPush = [&]()
    {
        if (chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm]->getPieceColor() !=
        chessBoard[position.row][position.collumm] -> getPieceColor())
        {
            listOfChessMoves.push_back(newChessMove);
        }
    };

    conditionalListOfChessMovesPush();
    newChessMove.newPosition.collumm--;
    conditionalListOfChessMovesPush();
    newChessMove.newPosition.collumm--;
    conditionalListOfChessMovesPush();
    newChessMove.newPosition.row--;
    conditionalListOfChessMovesPush();
    newChessMove.newPosition.row--;
    conditionalListOfChessMovesPush();
    newChessMove.newPosition.collumm++;
    conditionalListOfChessMovesPush();
    newChessMove.newPosition.collumm++;
    conditionalListOfChessMovesPush();
    newChessMove.newPosition.row++;
    conditionalListOfChessMovesPush();
    
}

void queenPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                          std::vector<chessMove>(&listOfChessMoves))
{
    chessPosition testPosition = position;
    bool ranIntoPiece = false;
    while (++testPosition.row < 8 && ++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        listOfChessMoves.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && ++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        listOfChessMoves.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.row < 8 && --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        listOfChessMoves.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        listOfChessMoves.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.row < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        listOfChessMoves.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        listOfChessMoves.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        listOfChessMoves.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while ( --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        listOfChessMoves.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
}

void bishopPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                           std::vector<chessMove>(&chessMovesVector))
{
    chessPosition testPosition = position;
    bool ranIntoPiece = false;
    while (++testPosition.row < 8 && ++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        chessMovesVector.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && ++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        chessMovesVector.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.row < 8 && --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        chessMovesVector.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1)
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        chessMovesVector.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
}

void knightPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                           std::vector<chessMove>(&chessMovesVector))
{
    chessMove newChessMove = {position, position.row+1, position.collumm+2};
    auto conditionalListOfChessMovesPush = [&]()
    {
        std::cout << "Getting all possible moves for Knight!"<< std::endl;

        if (newChessMove.newPosition.row < 8 && newChessMove.newPosition.collumm<8 && newChessMove.newPosition.row>-1 && newChessMove.newPosition.collumm >-1)
        {
            std::cout << "Checking (row,collumm):" << newChessMove.newPosition.row << ", " << newChessMove.newPosition.collumm << std::endl;
        if (chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm] -> getPieceColor() !=
        chessBoard[position.row][position.collumm] -> getPieceColor())
        {
            chessMovesVector.push_back(newChessMove);
            std::cout << "Adding possible chess move: (Original Space, New Space) (Row, Collumm): " << std::endl;
            std::cout << newChessMove.originalPosition.row << ", " << newChessMove.originalPosition.collumm << std::endl;
            std::cout << newChessMove.newPosition.row << ", " << newChessMove.newPosition.collumm << std::endl;
        }
        }
    };

    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row+2, position.collumm+1};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row+2, position.collumm-1};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row+1, position.collumm-2};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row-1, position.collumm-2};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row-2, position.collumm-1};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row-2, position.collumm+1};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row-1, position.collumm+2};
    conditionalListOfChessMovesPush();

}

void rookPieceModel::getAllPossibleMoves(const chessPosition position,chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<chessMove>(&chessMovesVector))
{       
    chessPosition testPosition = position;
    bool ranIntoPiece = false;
    while (++testPosition.row < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != this->getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        chessMovesVector.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != this->getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        chessMovesVector.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != -this->getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        chessMovesVector.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while ( --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == this->getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        chessMovesVector.push_back(newChessMove);
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
}

void pawnPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<chessMove>(&chessMovesVector))
{
    chessMove newMove;
    std::cout << "Chess Piece Direction: " << direction << std::endl;
    
    if ((position.row + direction) < 8 && (position.row + direction) > -1)
    {
    
    if (position.collumm+1 < 8)
    {
    if ((chessBoard[position.row + direction][position.collumm+1]->getPieceColor() != this->getPieceColor() && 
    chessBoard[position.row + direction][position.collumm+1]->getPieceColor() != -1) ||
    ( this -> enPassent_Info.movedTwoSpaces==true && this -> enPassent_Info.lastPawnMove.newPosition.row == position.row && 
    this -> enPassent_Info.lastPawnMove.newPosition.collumm == position.collumm+1))
    {
        newMove = {position, (position.row+direction), (position.collumm+1)};
        chessMovesVector.push_back(newMove);
    }
    }
    if (position.collumm-1 > -1)
    {
    if ((chessBoard[position.row + direction][position.collumm-1]->getPieceColor() != this->getPieceColor() && 
    chessBoard[position.row + direction][position.collumm-1]->getPieceColor() != -1) ||
    ( this->enPassent_Info.movedTwoSpaces==true && this->enPassent_Info.lastPawnMove.newPosition.row == position.row && 
    this->enPassent_Info.lastPawnMove.newPosition.collumm == position.collumm-1))
    {
        newMove = {position, (position.row+direction), (position.collumm-1)};
        chessMovesVector.push_back(newMove);
    }
    }
    
    if (chessBoard[position.row + direction][position.collumm]->getPieceColor() == -1)
    {
        newMove = {position, (position.row+direction), (position.collumm)};
        chessMovesVector.push_back(newMove);
    }
    }
    if ((position.row + (2*direction)) < 8 && (position.row + (2*direction)) >-1 )
    {
    if (chessBoard[position.row + (2*direction)][position.collumm]->getPieceColor() == -1)
    {
        newMove = {position, (position.row+(2*direction)), (position.collumm)};
        chessMovesVector.push_back(newMove);
        enPassent_Info = {true, newMove};
    }
    }
}

void nullPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<chessMove>(&chessMovesVector))
{
}


void pawnPieceModel::setDirection(int changeofRow)
{
    direction = changeofRow;
}

void magicFunction() //This function isn't used anywhere. It's just here to avoid linker errors for the kingPieceModel's template.
//This is complete vodoo magic.
{
    kingPieceModel<2,2> tempKing(0);
}