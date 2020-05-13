#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <vector>
#include <array>
#include <string>

namespace chessModelInformation
{

    struct chessPosition
    {
        int row;
        int collumm;

        bool operator==(const chessPosition &position);
    };

    struct chessMove
    {
        chessPosition originalPosition;
        chessPosition newPosition;
        bool enPessant = false;

        bool operator==(const chessMove &move);
    };

    int findInFirstElement(std::vector<std::vector<chessMove>> &listOfChessMoves, chessMove testMove);
    
    struct enPassantInfo
    {
        chessMove lastPawnMove;
    };

    class chessPieceModel
    {
    protected:
        short pieceColor;

    public:
        int getPieceColor() const;

    public:
        chessPieceModel(int pieceColorNum) : pieceColor(pieceColorNum){};
        chessPieceModel(){};

        bool isMoved = false;

        virtual void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<std::vector<chessMove>>(&listOfChessMoves)) = 0;
    };

    struct castlingInformation
    {
        std::vector<chessPosition> chessPositionsToCheck;
        std::vector<chessPosition> chessPositionsToClear;
        chessPosition positionToMoveKingTo;
        chessPosition positionToMoveCastilingPieceTo;
        chessPosition positionOfCastlingPiece;
        chessPieceModel *chessPieceToCastle;
    };

    class kingPieceModel : public chessPieceModel
    {
        using chessPieceModel::chessPieceModel;

    public:
        std::vector<castlingInformation> castlingParameters;
        void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                 std::vector<std::vector<chessMove>>(&listOfChessMoves)) override;
        void getAllPossibleCastlingMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                         std::vector<std::vector<chessMove>>(&listOfChessMoves));
        kingPieceModel(int pieceColorNum, std::vector<castlingInformation> &castlingParam)
            : chessPieceModel(pieceColorNum), castlingParameters(castlingParam){};
        kingPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
        kingPieceModel(){};
    };

    class queenPieceModel : public chessPieceModel
    {
        using chessPieceModel::chessPieceModel;

    public:
        void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                 std::vector<std::vector<chessMove>>(&listOfChessMoves)) override;
        queenPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
        queenPieceModel(){};
    };

    class bishopPieceModel : public chessPieceModel
    {
        using chessPieceModel::chessPieceModel;

    public:
        void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                 std::vector<std::vector<chessMove>>(&listOfChessMoves)) override;
        bishopPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
        bishopPieceModel(){};
    };

    class knightPieceModel : public chessPieceModel
    {
        using chessPieceModel::chessPieceModel;

    public:
        void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                 std::vector<std::vector<chessMove>>(&listOfChessMoves)) override;
        knightPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
        knightPieceModel(){};
    };

    class rookPieceModel : public chessPieceModel
    {
        bool isMoved = false;
        using chessPieceModel::chessPieceModel;

    public:
        bool getIsMoved(const chessPieceModel *(&chessBoard)[8][8]);
        bool getIsAbleToCastle(const chessPosition position, const chessPieceModel *(&chessBoard)[8][8]);
        void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                 std::vector<std::vector<chessMove>>(&listOfChessMoves)) override;
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
                                 std::vector<std::vector<chessMove>>(&listOfChessMoves)) override;
        pawnPieceModel(int pieceColorNum) : chessPieceModel(pieceColorNum){};
        pawnPieceModel(){};
    };

    class nullPieceModel : public chessPieceModel
    {
        using chessPieceModel::chessPieceModel;

    public:
        void getAllPossibleMoves(const chessPosition position, chessPieceModel *(&chessBoard)[8][8],
                                 std::vector<std::vector<chessMove>>(&listOfChessMoves)) override;
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
    void setChessPiece(chessPieceModel *chesspiece, chessPosition position);
    void movePiece(chessMove move);
    bool checkMove(chessMove move);
    void getAllPossibleBasicMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves));
    void getAllPossibleBasicMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves), chessPosition position);
    void getAllPossibleBasicMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves), int color);
    void getAllPossibleCastlingMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves));
    void getAllPossibleCastlingMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves), chessPosition position);
    void getAllPossibleCastlingMoves(std::vector<std::vector<chessMove>>(&listOfChessMoves), int color);
    bool checkIfSpaceIsAttacked(chessPosition spaceBeingAttacked, int defendingColor);
    int getPieceOnSpaceColor(chessPosition position);
};

#endif