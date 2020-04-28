#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include <array>


namespace chessModelInformation
{

struct chessPosition
{
    int row;
    int collumm;
};

struct chessMove
{
    chessPosition originalPosition;
    chessPosition newPosition;
};

struct enPassantInfo
{
    bool movedTwoSpaces = false;
    chessMove lastPawnMove;
};

class chessPieceModel
{
protected:
    virtual void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves)) = 0;
    int pieceColor;
    public:
    bool checkMove(const chessMove (&move),chessPieceModel *(&chessBoard)[8][8]);
    int getPieceColor () const;

public:
    chessPieceModel(int pieceColorNum) : pieceColor(pieceColorNum){};
    chessPieceModel(){};
};

template <std::size_t numberOfChessPositionsToCheck>
struct castlingInformation
{
    std::array<chessPosition, numberOfChessPositionsToCheck> chessPositionsToCheck;
    chessPosition positionToMoveKingTo;
    chessPosition positionToMoveCastilingPieceTo;
    chessPieceModel* chessPieceToCastle;
};

template <std::size_t numberOfCastlingObjects,std::size_t numberOfChessPositionsToCheck>
class kingPieceModel : public chessPieceModel
{
    
    bool isMoved = false;
    std::array <castlingInformation<numberOfChessPositionsToCheck>, numberOfCastlingObjects> castlingParameters; 
    using chessPieceModel::chessPieceModel;
    public:
    bool getIsMoved();
    void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves)) override;
    kingPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
    kingPieceModel(){};
};

class queenPieceModel : public chessPieceModel
{
    using chessPieceModel::chessPieceModel;
    public:
    void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves)) override;
    queenPieceModel(int pieceColorNum) :chessPieceModel(pieceColorNum){};
    queenPieceModel(){};
};

class bishopPieceModel : public chessPieceModel
{
    using chessPieceModel::chessPieceModel;
    public:
    void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves)) override;
    bishopPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
    bishopPieceModel(){};
   
};

class knightPieceModel : public chessPieceModel
{
    using chessPieceModel::chessPieceModel;
    public:
    void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves)) override;
    knightPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
    knightPieceModel(){};
};

class rookPieceModel : public chessPieceModel
{
    bool isMoved = false;
    using chessPieceModel::chessPieceModel;
    public:
    bool getIsMoved(const chessPieceModel *(&chessBoard)[8][8]);
    bool getIsAbleToCastle(const chessPosition  position,const chessPieceModel *(&chessBoard)[8][8]);
    void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves)) override;
    rookPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
    rookPieceModel(){};
    
};

class pawnPieceModel : public chessPieceModel
{
    int direction;
    using chessPieceModel::chessPieceModel;
    public:
    static enPassantInfo enPassent_Info;
    void setDirection(int changeofRow);
    void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves)) override;
    pawnPieceModel(int pieceColorNum) :chessPieceModel(pieceColorNum){};
    pawnPieceModel(){};
    
};

class nullPieceModel : public chessPieceModel
{
    using chessPieceModel::chessPieceModel;
    public:
    void getAllPossibleMoves(const chessPosition  position, chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves)) override;
    nullPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
    nullPieceModel(){};
    
};

} // namespace chessModelInformation

using namespace chessModelInformation;
class chessModel
{   
    chessPieceModel *chessBoard[8][8];
   
    public:
    chessModel();
    void setChessPiece(chessPieceModel* chesspiece, chessPosition position);
    void movePiece(chessPosition originalPosition, chessPosition newPosition);
    bool checkMove(chessPosition originalPosition, chessPosition newPosition);

};

#endif