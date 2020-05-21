#include "model.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace chessModelInformation;

chessMove enPassentInfo;

chessMove &pawnPieceModel::enPassent_Info = enPassentInfo;

extern nullPieceModel defaultnullPieceModel;

int chessModelInformation::findInFirstElement(std::vector<std::vector<chessMove>> &listOfChessMoves, chessMove testMove)
{
    for (int i = 0; i < listOfChessMoves.size(); i++)
    {
        if (listOfChessMoves[i][0] == testMove)
        {
            return i;
        }
    }
    return -1;
}

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
    std::vector<std::vector<chessMove>> listOfChessMoves;
    chessBoard[move.originalPosition.row][move.originalPosition.collumm]->getAllPossibleMoves(move.originalPosition, chessBoard, listOfChessMoves);

    return findInFirstElement(listOfChessMoves, move);
}

void chessModel::setChessPiece(chessPieceModel *chesspiece, chessPosition position)
{
    chessBoard[position.row][position.collumm] = chesspiece;
}

void chessModel::movePiece(chessMove &move)
{
    enPassentInfo = move;
    chessBoard[move.originalPosition.row][move.originalPosition.collumm]->isMoved = true;
    chessBoard[move.newPosition.row][move.newPosition.collumm] = chessBoard[move.originalPosition.row][move.originalPosition.collumm];
    chessBoard[move.originalPosition.row][move.originalPosition.collumm] = &defaultnullPieceModel;

    std::vector<chessPosition>::iterator it = std::find(positionOfChessPiecesToNotAttacked.begin(), positionOfChessPiecesToNotAttacked.end(), move.originalPosition);
    if (it != positionOfChessPiecesToNotAttacked.end())
    {
        *it = move.newPosition;
        move.noAttackPieceMoved = true;
    }
}

void chessModel::reverseMove(chessMove &move)
{
    chessBoard[move.originalPosition.row][move.originalPosition.collumm] = chessBoard[move.newPosition.row][move.newPosition.collumm];
    chessBoard[move.newPosition.row][move.newPosition.collumm] = move.replacedPiece;
    if (move.firstMove)
    {
        chessBoard[move.originalPosition.row][move.originalPosition.collumm]->isMoved = false;
    }
    std::vector<chessPosition>::iterator it = std::find(positionOfChessPiecesToNotAttacked.begin(), positionOfChessPiecesToNotAttacked.end(), move.newPosition);
    if (move.noAttackPieceMoved)
    {
        *it = move.originalPosition;
        move.noAttackPieceMoved = false;
    }
    enPassentInfo.enPessant = false;
}

void chessModel::getAllPossibleMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves))
{
    for (int row = 0; row < 8; row++)
    {
        for (int collumm = 0; collumm < 8; collumm++)
        {
            chessBoard[row][collumm]->getAllPossibleMoves({row, collumm}, chessBoard, listOfChessMoves);
        }
    }
}

void chessModel::getAllPossibleBasicMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves), chessPosition position)
{
    chessBoard[position.row][position.collumm]->getAllPossibleMoves(position, chessBoard, listOfChessMoves);
}

void chessModel::getAllPossibleBasicMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves), int color)
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

inline bool checkIfSpaceIsAttackedFunction(std::vector<chessPosition> spaceBeingAttacked, int defendingColor, chessModelInformation::chessPieceModel *(&chessBoard)[8][8])
{
    std::vector<std::vector<chessMove>> listOfChessMoves;
    for (int row = 0; row < 8; row++)
    {
        for (int collumm = 0; collumm < 8; collumm++)
        {
            if (chessBoard[row][collumm]->getPieceColor() != defendingColor)
            {
                chessPosition Testposition = {row, collumm};
                chessBoard[row][collumm]->getAllPossibleMoves(Testposition, chessBoard, listOfChessMoves);
            }
        }
    }

    for (int j = 0; j < spaceBeingAttacked.size(); j++)
    {
        for (int i = 0; i < listOfChessMoves.size(); i++)
        {
            if (listOfChessMoves[i][0].newPosition == spaceBeingAttacked[j])
            {
                return true;
            }
        }
    }
    return false;
}

bool chessModel::checkIfSpaceIsAttacked(std::vector<chessPosition> spaceBeingAttacked, int defendingColor)
{
    return checkIfSpaceIsAttackedFunction(spaceBeingAttacked, defendingColor, chessBoard);
}

int chessModel::getPieceOnSpaceColor(chessPosition position)
{
    return chessBoard[position.row][position.collumm]->getPieceColor();
}

void chessModel::clearSpacesToNotAttackAfterMove(std::vector<std::vector<chessMove>>(&listOfChessMoves), int defendingColor)
{

    for (int i = 0; i < listOfChessMoves.size(); i++)
    {
        for (int j = 0; j < listOfChessMoves[i].size(); j++)
        {
            movePiece(listOfChessMoves[i][j]);
        }


        std::vector<chessPosition> chessPositionsToCheck;
        for (int k = 0; k < positionOfChessPiecesToNotAttacked.size(); k++)
        {
            if (chessBoard[positionOfChessPiecesToNotAttacked[k].row][positionOfChessPiecesToNotAttacked[k].collumm]->getPieceColor() == defendingColor)
            {
                chessPositionsToCheck.push_back(positionOfChessPiecesToNotAttacked[k]);
            }
        }

        if (checkIfSpaceIsAttacked(chessPositionsToCheck, defendingColor))
        {   
            for (int j = (listOfChessMoves[i].size() - 1); j >= 0; j--)
            {
                reverseMove(listOfChessMoves[i][j]);
            }

            listOfChessMoves.erase(listOfChessMoves.begin() + i);
            i--;
        }
        else
        {
            for (int j = (listOfChessMoves[i].size() - 1); j >= 0; j--)
            {
                reverseMove(listOfChessMoves[i][j]);
            }
        }
    }

    std::cout << std::endl;
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

bool kingPieceModel::castling = true;

void kingPieceModel::getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<std::vector<chessMove>>(&listOfChessMoves))
{
    chessMove newChessMove = {position, position.row + 1, position.collumm + 1};
    newChessMove.firstMove = !isMoved;
    auto conditionalListOfChessMovesPush = [&]() {
        if (newChessMove.newPosition.row < 8 && newChessMove.newPosition.collumm < 8 && newChessMove.newPosition.row > -1 && newChessMove.newPosition.collumm > -1)
        {
            if (chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm]->getPieceColor() !=
                getPieceColor())
            {
                newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
                listOfChessMoves.push_back({newChessMove});
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

    if (castling)
    {
        getAllPossibleCastlingMoves(position, chessBoard, listOfChessMoves);
    }
}

void kingPieceModel::getAllPossibleCastlingMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                                 std::vector<std::vector<chessMove>>(&listOfChessMoves))
{
    castling = false;
    if (!isMoved)
    {
        for (int i = 0; i < castlingParameters.size(); i++)
        {
            if (!(castlingParameters[i].chessPieceToCastle->isMoved))
            {
                bool movePiece = true;
                for (int k = 0; k < castlingParameters[i].chessPositionsToClear.size(); k++)
                {
                    if ((chessBoard[castlingParameters[i].chessPositionsToClear[k].row][castlingParameters[i].chessPositionsToClear[k].collumm]->getPieceColor()) != -1)
                    {
                        movePiece = false;
                        k = castlingParameters[i].chessPositionsToClear.size();
                    }
                }
                if (movePiece)
                {
                    if (!checkIfSpaceIsAttackedFunction(castlingParameters[i].chessPositionsToCheck, pieceColor, chessBoard))
                    {
                        chessMove move = {position, castlingParameters[i].positionToMoveKingTo};
                        move.firstMove = true;
                        move.replacedPiece = chessBoard[move.newPosition.row][move.newPosition.collumm];
                        listOfChessMoves.push_back({move});
                        move.originalPosition = castlingParameters[i].positionOfCastlingPiece;
                        move.newPosition = castlingParameters[i].positionToMoveCastilingPieceTo;
                        move.replacedPiece = chessBoard[move.newPosition.row][move.newPosition.collumm];
                        listOfChessMoves.back().push_back({move});
                    }
                }
            }
        }
    }
    castling = true;
}

void queenPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                          std::vector<std::vector<chessMove>>(&listOfChessMoves))
{
    chessPosition testPosition = position;
    bool ranIntoPiece = false;
    while (++testPosition.row < 8 && ++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        listOfChessMoves.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && ++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        listOfChessMoves.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.row < 8 && --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        listOfChessMoves.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        listOfChessMoves.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.row < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        listOfChessMoves.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        listOfChessMoves.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        listOfChessMoves.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        listOfChessMoves.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
}

void bishopPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                           std::vector<std::vector<chessMove>>(&chessMovesVector))
{
    chessPosition testPosition = position;
    bool ranIntoPiece = false;
    while (++testPosition.row < 8 && ++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        chessMovesVector.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && ++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        chessMovesVector.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.row < 8 && --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        chessMovesVector.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && --testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        chessMovesVector.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
}

void knightPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                           std::vector<std::vector<chessMove>>(&chessMovesVector))
{
    chessMove newChessMove = {position, position.row + 1, position.collumm + 2};
    auto conditionalListOfChessMovesPush = [&]() {
        if (newChessMove.newPosition.row < 8 && newChessMove.newPosition.collumm < 8 && newChessMove.newPosition.row > -1 && newChessMove.newPosition.collumm > -1)
        {
            if (chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm]->getPieceColor() !=
                chessBoard[position.row][position.collumm]->getPieceColor())
            {
                newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
                newChessMove.firstMove = !isMoved;
                chessMovesVector.push_back({newChessMove});
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
                                         std::vector<std::vector<chessMove>>(&chessMovesVector))
{
    chessPosition testPosition = position;
    bool ranIntoPiece = false;
    while (++testPosition.row < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        chessMovesVector.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.row > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        chessMovesVector.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (++testPosition.collumm < 8 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        chessMovesVector.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
    testPosition = position;
    ranIntoPiece = false;
    while (--testPosition.collumm > -1 && ranIntoPiece == false &&
           chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() != getPieceColor())
    {
        chessMove newChessMove = {position, testPosition.row, testPosition.collumm};
        newChessMove.replacedPiece = chessBoard[newChessMove.newPosition.row][newChessMove.newPosition.collumm];
        newChessMove.firstMove = !isMoved;
        chessMovesVector.push_back({newChessMove});
        ranIntoPiece = (chessBoard[testPosition.row][testPosition.collumm]->getPieceColor() == -1) ? false : true;
    }
}

void pawnPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<std::vector<chessMove>>(&chessMovesVector))
{
    chessMove newMove;

    if ((position.row + direction) < 8 && (position.row + direction) > -1)
    {

        if (position.collumm + 1 < 8)
        {
            if ((enPassent_Info.enPessant == true) && (enPassent_Info.newPosition.row == position.row) &&
                (enPassent_Info.newPosition.collumm == (position.collumm + 1)))
            {

                std::cout << "Enpessent to (row, collumm): " << (position.row + direction) << ", " << (position.collumm + 1) << std::endl;
                newMove = {position, (position.row + direction), (position.collumm + 1)};
                newMove.replacedPiece = chessBoard[newMove.newPosition.row][newMove.newPosition.collumm];
                newMove.firstMove = !isMoved;
                chessMovesVector.push_back({newMove});
                newMove = {position, enPassent_Info.newPosition, this, !isMoved};
                chessMovesVector.back().push_back({newMove});
            }

            else if ((chessBoard[position.row + direction][position.collumm + 1]->getPieceColor() != this->getPieceColor() &&
                      chessBoard[position.row + direction][position.collumm + 1]->getPieceColor() != -1))
            {
                newMove = {position, (position.row + direction), (position.collumm + 1)};
                newMove.replacedPiece = chessBoard[newMove.newPosition.row][newMove.newPosition.collumm];
                newMove.firstMove = !isMoved;
                chessMovesVector.push_back({newMove});
            }
        }
        if (position.collumm - 1 > -1)
        {
            if ((enPassent_Info.enPessant == true) && (enPassent_Info.newPosition.row == position.row) &&
                (enPassent_Info.newPosition.collumm == (position.collumm - 1)))
            {
                std::cout << "Enpessent to (row, collumm): " << (position.row + direction) << ", " << (position.collumm + 1) << std::endl;
                newMove = {position, (position.row + direction), (position.collumm - 1)};
                newMove.replacedPiece = chessBoard[newMove.newPosition.row][newMove.newPosition.collumm];
                newMove.firstMove = !isMoved;
                chessMovesVector.push_back({newMove});
                newMove = {position, enPassent_Info.newPosition};
                newMove.replacedPiece = chessBoard[newMove.newPosition.row][newMove.newPosition.collumm];
                newMove.firstMove = !isMoved;
                chessMovesVector.back().push_back({newMove});
            }

            else if ((chessBoard[position.row + direction][position.collumm - 1]->getPieceColor() != this->getPieceColor() &&
                      chessBoard[position.row + direction][position.collumm - 1]->getPieceColor() != -1))
            {
                newMove = {position, (position.row + direction), (position.collumm - 1)};
                newMove.replacedPiece = chessBoard[newMove.newPosition.row][newMove.newPosition.collumm];
                newMove.firstMove = !isMoved;
                chessMovesVector.push_back({newMove});
            }
        }

        if (chessBoard[position.row + direction][position.collumm]->getPieceColor() == -1)
        {
            newMove = {position, (position.row + direction), (position.collumm)};
            newMove.replacedPiece = chessBoard[newMove.newPosition.row][newMove.newPosition.collumm];
            newMove.firstMove = !isMoved;
            chessMovesVector.push_back({newMove});
        }
    }
    if (((position.row + (2 * direction)) < 8) && ((position.row + (2 * direction)) > -1) && (isMoved == false))
    {
        if (chessBoard[position.row + (2 * direction)][position.collumm]->getPieceColor() == -1)
        {
            newMove = {position, {(position.row + (2 * direction)), (position.collumm)}};
            newMove.replacedPiece = chessBoard[newMove.newPosition.row][newMove.newPosition.collumm];
            newMove.firstMove = !isMoved;
            chessMovesVector.push_back({newMove});
        }
    }
}

void nullPieceModel::getAllPossibleMoves(const chessPosition position, chessModelInformation::chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<std::vector<chessMove>>(&chessMovesVector))
{
}

void pawnPieceModel::setDirection(int changeofRow)
{
    direction = changeofRow;
}