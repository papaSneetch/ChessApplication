#ifndef MODEL_HPP
#define MODEL_HPP


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
std::vector<chessMove> (&listOfChessMoves)){};
    signed char pieceColor; // -1 is a null piece. Char is used to save memory.
    public:
    bool checkMove(const chessMove (&move),chessPieceModel *(&chessBoard)[8][8]);
    signed char getPieceColor () const;

public:
    chessPieceModel(signed char pieceColorNum) : pieceColor(pieceColorNum){};
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
    void getAllPossibleMoves(const chessPosition  position,const chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves));
    kingPieceModel(signed char pieceColorNum) : chessPieceModel(pieceColorNum){};
    kingPieceModel(){};
};

class queenPieceModel : public chessPieceModel
{
    using chessPieceModel::chessPieceModel;
    public:
    void getAllPossibleMoves(const chessPosition  position,const chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves));
    queenPieceModel(signed char pieceColorNum) :chessPieceModel(pieceColorNum){};
    queenPieceModel(){};
};

class bishopPieceModel : public chessPieceModel
{
    using chessPieceModel::chessPieceModel;
    public:
    void getAllPossibleMoves(const chessPosition  position,const chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves));
    bishopPieceModel(signed char pieceColorNum) : chessPieceModel(pieceColorNum){};
    bishopPieceModel(){};
   
};

class knightPieceModel : public chessPieceModel
{
    using chessPieceModel::chessPieceModel;
    public:
    void getAllPossibleMoves(const chessPosition  position,const chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves));
    knightPieceModel(signed char pieceColorNum) : chessPieceModel(pieceColorNum){};
    knightPieceModel(){};
};

class rookPieceModel : public chessPieceModel
{
    bool isMoved = false;
    using chessPieceModel::chessPieceModel;
    public:
    bool getIsMoved(const chessPieceModel *(&chessBoard)[8][8]);
    bool getIsAbleToCastle(const chessPosition  position,const chessPieceModel *(&chessBoard)[8][8]);
    void getAllPossibleMoves(const chessPosition  position,const chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves));
    rookPieceModel(signed char pieceColorNum) : chessPieceModel(pieceColorNum){};
    rookPieceModel(){};
    
};

class pawnPieceModel : public chessPieceModel
{
    int direction;
    using chessPieceModel::chessPieceModel;
    public:
    static enPassantInfo enPassent_Info;
    void getAllPossibleMoves(const chessPosition position,const chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves));
    pawnPieceModel(signed char pieceColorNum) :chessPieceModel(pieceColorNum){};
    pawnPieceModel(){};
    
};

class nullPieceModel : public chessPieceModel
{
    using chessPieceModel::chessPieceModel;
    public:
    void getAllPossibleMoves(const chessPosition  position,const chessPieceModel *(&chessBoard)[8][8],
std::vector<chessMove> (&listOfChessMoves));
    nullPieceModel(signed char pieceColorNum) : chessPieceModel(pieceColorNum){};
    nullPieceModel(){};
    
};

} // namespace chessModelInformation

using namespace chessModelInformation;
class chessModel
{   
    chessPieceModel *chessBoard[8][8];
   
    public:
    void setChessPiece(chessPieceModel* chesspiece, chessPosition position);
    void movePiece(chessPosition originalPosition, chessPosition newPosition);
    bool checkMove(chessPosition originalPosition, chessPosition newPosition);

};

#endif