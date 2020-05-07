#include "model.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace chessModelInformation;

enPassantInfo pawnPieceModel::enPassent_Info;

extern nullPieceModel defaultnullPieceModel;

bool chessPosition::operator==(const chessPosition &position)
{
    if ((row == position.row) && (collumm == position.collumm))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool chessMove::operator==(const chessMove &move)
{
    if ((originalPosition == move.originalPosition) && (newPosition == move.newPosition))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool chessModel::checkMove(chessMove move)
{
    std::vector<chessMove> listOfChessMoves;
    chessBoard[move.originalPosition.row][move.originalPosition.collumm]->getAllPossibleMoves(move.originalPosition, chessBoard, listOfChessMoves);

    if (std::find(listOfChessMoves.begin(), listOfChessMoves.end(), move) != listOfChessMoves.end())
    {
        return true;
    }
    return false;
}

void chessModel::setChessPiece(chessPieceModel *chesspiece, chessPosition position)
{
    chessBoard[position.row][position.collumm] = chesspiece;
}

void chessModel::movePiece(chessMove move)
{
    chessBoard[move.originalPosition.row][move.originalPosition.collumm]->isMoved = true;
    chessBoard[move.newPosition.row][move.newPosition.collumm] = chessBoard[move.originalPosition.row][move.originalPosition.collumm];
    chessBoard[move.originalPosition.row][move.originalPosition.collumm] = &defaultnullPieceModel;
}

void chessModel::getAllPossibleBasicMoves(std::vector<chessMove>(&listOfChessMoves))
{
    for (int row = 0; row < 8; row++)
    {
        for (int collumm = 0; collumm < 8; collumm++)
        {
            chessBoard[row][collumm]->getAllPossibleMoves({row, collumm}, chessBoard, listOfChessMoves);
        }
    }
}

void chessModel::getAllPossibleBasicMoves(std::vector<chessMove>(&listOfChessMoves), chessPosition position)
{
    chessBoard[position.row][position.collumm]->getAllPossibleMoves(position, chessBoard, listOfChessMoves);
}

void chessModel::getAllPossibleBasicMoves(std::vector<chessMove>(&listOfChessMoves), int color)
{
    for (int row = 0; row < 8; row++)
    {
        for (int collumm = 0; collumm < 8; collumm++)
        {
            if (chessBoard[row][collumm]->getPieceColor() == color)
            {
                chessBoard[row][collumm]->getAllPossibleMoves({row, collumm}, chessBoard, listOfChessMoves);
            }
        }
    }
}

void chessModel::getAllPossibleCastlingMoves(std::vector<chessMove>(&listOfChessMoves), chessPosition position)
{
    kingPieceModel *testPiece = dynamic_cast<kingPieceModel *>(chessBoard[position.row][position.collumm]);
    if (testPiece)
    {
        testPiece->getAllPossibleCastlingMoves(position, chessBoard, listOfChessMoves);
    }
}

bool checkIfSpaceIsAttackedFunction(chessPosition spaceBeingAttacked, int defendingColor, chessModelInformation::chessPieceModel *(&chessBoard)[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int collumm = 0; collumm < 8; collumm++)
        {
            int currentColor = chessBoard[row][collumm]->getPieceColor();
            if ((currentColor != defendingColor) && (currentColor != -1))
            {
                std::vector<chessMove> listOfChessMoves;
                chessPosition Testposition = {row, collumm};
                chessBoard[row][collumm]->getAllPossibleMoves(Testposition, chessBoard, listOfChessMoves);
                for (int i = 0; i < listOfChessMoves.size(); i++)
                {
                    if ((listOfChessMoves[i].newPosition.row == spaceBeingAttacked.row) &&
                        (listOfChessMoves[i].newPosition.collumm == spaceBeingAttacked.collumm))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool chessModel::checkIfSpaceIsAttacked(chessPosition spaceBeingAttacked, int defendingColor)
{
    return checkIfSpaceIsAttackedFunction(spaceBeingAttacked, defendingColor, this->chessBoard);
}

int chessModel::getPieceOnSpaceColor(chessPosition position)
{
    return chessBoard[position.row][position.collumm] -> getPieceColor();
}

chessModel::chessModel()
{
    chessPosition position;
    for (int row = 0; row < 8; row++)
    {
        for (int collumm = 0; collumm < 8; collumm++)
        {
            position.row = row;
            position.collumm = collumm;
            setChessPiece(&defaultnullPieceModel, position);
        }
    }
}

int chessPieceModel::getPieceColor() const
{
    return pieceColor;
}

void kingPieceModel::getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<chessMove>(&listOfChessMoves))
{
    chessMove newChessMove = {position, position.row + 1, position.collumm + 1};
    auto conditionalListOfChessMovesPush = [&]() {
        if (newChessMove.newPosition.row < 8 && newChessMove.newPosition.collumm < 8 && newChessMove.newPosition.row > -1 && newChessMove.newPosition.collumm > -1)
        {
            if (chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm]->getPieceColor() !=
                this->getPieceColor())
            {
                listOfChessMoves.push_back(newChessMove);
            }
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

void kingPieceModel::getAllPossibleCastlingMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8], std::vector<chessMove>(&listOfChessMoves))
{
    if (!isMoved)
    {
        for (int i = 0; i < castlingParameters.size(); i++)
        {
            bool movePiece = true;
            if (!(castlingParameters[i].chessPieceToCastle->isMoved))
            {
                for (int j = 0; j < castlingParameters[i].chessPositionsToCheck.size(); j++)
                {
                    for (int k=0; k<castlingParameters[i].chessPositionsToClear.size(); k++)
                    {
                        if ((chessBoard[castlingParameters[i].chessPositionsToClear[k].row][castlingParameters[i].chessPositionsToClear[k].collumm] -> getPieceColor()) != -1)
                        {
                            movePiece = false;
                            j = castlingParameters[i].chessPositionsToCheck.size();
                            k = castlingParameters[i].chessPositionsToClear.size();
                        }
                        else if (checkIfSpaceIsAttackedFunction(castlingParameters[i].chessPositionsToCheck[j], pieceColor, chessBoard))
                        {
                            movePiece = false;
                            j = castlingParameters[i].chessPositionsToCheck.size();
                            k = castlingParameters[i].chessPositionsToClear.size();
                        }
                    }
                }
                if (movePiece)
                {
                    chessMove move = {position, castlingParameters[i].positionToMoveKingTo};
                    listOfChessMoves.push_back(move);
                    move = {castlingParameters[i].positionOfCastlingPiece, castlingParameters[i].positionToMoveCastilingPieceTo};
                    listOfChessMoves.push_back(move);
                }
            }
        }
    }
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
    while (--testPosition.collumm > -1 && ranIntoPiece == false &&
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
    chessMove newChessMove = {position, position.row + 1, position.collumm + 2};
    auto conditionalListOfChessMovesPush = [&]() {
        if (newChessMove.newPosition.row < 8 && newChessMove.newPosition.collumm < 8 && newChessMove.newPosition.row > -1 && newChessMove.newPosition.collumm > -1)
        {
            if (chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm]->getPieceColor() !=
                chessBoard[position.row][position.collumm]->getPieceColor())
            {
                chessMovesVector.push_back(newChessMove);
            }
        }
    };

    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row + 2, position.collumm + 1};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row + 2, position.collumm - 1};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row + 1, position.collumm - 2};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row - 1, position.collumm - 2};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row - 2, position.collumm - 1};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row - 2, position.collumm + 1};
    conditionalListOfChessMovesPush();
    newChessMove = {position, position.row - 1, position.collumm + 2};
    conditionalListOfChessMovesPush();
}

void rookPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
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
    while (--testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != this->getPieceColor())
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

        if (position.collumm + 1 < 8)
        {
            if ((chessBoard[position.row + direction][position.collumm + 1]->getPieceColor() != this->getPieceColor() &&
                 chessBoard[position.row + direction][position.collumm + 1]->getPieceColor() != -1) ||
                (this->enPassent_Info.movedTwoSpaces == true && this->enPassent_Info.lastPawnMove.newPosition.row == position.row &&
                 this->enPassent_Info.lastPawnMove.newPosition.collumm == position.collumm + 1))
            {
                newMove = {position, (position.row + direction), (position.collumm + 1)};
                chessMovesVector.push_back(newMove);
            }
        }
        if (position.collumm - 1 > -1)
        {
            if ((chessBoard[position.row + direction][position.collumm - 1]->getPieceColor() != this->getPieceColor() &&
                 chessBoard[position.row + direction][position.collumm - 1]->getPieceColor() != -1) ||
                (this->enPassent_Info.movedTwoSpaces == true && this->enPassent_Info.lastPawnMove.newPosition.row == position.row &&
                 this->enPassent_Info.lastPawnMove.newPosition.collumm == position.collumm - 1))
            {
                newMove = {position, (position.row + direction), (position.collumm - 1)};
                chessMovesVector.push_back(newMove);
            }
        }

        if (chessBoard[position.row + direction][position.collumm]->getPieceColor() == -1)
        {
            newMove = {position, (position.row + direction), (position.collumm)};
            chessMovesVector.push_back(newMove);
        }
    }
    if (((position.row + (2 * direction)) < 8) && ((position.row + (2 * direction)) > -1) && (isMoved == false))
    {
        if (chessBoard[position.row + (2 * direction)][position.collumm]->getPieceColor() == -1)
        {
            newMove = {position, (position.row + (2 * direction)), (position.collumm)};
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