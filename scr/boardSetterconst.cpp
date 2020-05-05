#include "boardSetter.hpp"

using namespace setUpBoard; 

extern kingPieceModel  whiteKingPieceModel;
extern kingPieceModel  blackKingPieceModel;
extern queenPieceModel whiteQueenPieceModel;
extern queenPieceModel blackQueenPieceModel;
extern bishopPieceModel whiteBishopPieceModel;
extern bishopPieceModel blackBishopPieceModel;
extern knightPieceModel whiteKnightPieceModel;
extern knightPieceModel blackKnightPieceModel;
extern rookPieceModel whiteRookPieceModelLeft;
extern rookPieceModel whiteRookPieceModelRight;
extern rookPieceModel blackRookPieceModelLeft;
extern rookPieceModel blackRookPieceModelRight;
extern pawnPieceModel whitePawnPieceModel;
extern pawnPieceModel blackPawnPieceModel;
extern nullPieceModel defaultnullPieceModel;


void setWhitePawnMetaData(chessWidget *chesswidget, chessModel* chessmodel)
{
    whitePawnPieceModel.setDirection(-1);
    blackPawnPieceModel.setDirection(1);
}

void setBlackPawnMetaData(chessWidget *chesswidget, chessModel* chessmodel)
{
    blackPawnPieceModel.setDirection(-1);
    whitePawnPieceModel.setDirection(1);
}

void setWhiteKingMetaData(chessWidget *chesswidget, chessModel* chessmodel)
{
    {
    std::vector <castlingInformation> whiteCastlingParameters;
    {
    std::vector <chessPosition> rookPositionsToCheck = {{7,4},{7,3}};
    std::vector <chessPosition> positionsToClear = {{7,3},{7,2},{7,1}};
    chessPosition positionToMoveKingTo = {7,2};
    chessPosition positionToMoveCastilingPieceTo = {7,3};
    chessPosition positionOfCastlingPiece = {7,0};
    castlingInformation castlingData = {rookPositionsToCheck,positionsToClear,positionToMoveKingTo,
    positionToMoveCastilingPieceTo, positionOfCastlingPiece, &whiteRookPieceModelLeft};
    whiteCastlingParameters.push_back(castlingData);
    }
    {
    std::vector <chessPosition> rookPositionsToCheck = {{7,4},{7,5}};
    std::vector <chessPosition> positionsToClear = {{7,5},{7,6}};
    chessPosition positionToMoveKingTo = {7,6};
    chessPosition positionToMoveCastilingPieceTo = {7,5};
    chessPosition positionOfCastlingPiece = {7,7};
    castlingInformation castlingData = {rookPositionsToCheck,positionsToClear,positionToMoveKingTo,
    positionToMoveCastilingPieceTo, positionOfCastlingPiece, &whiteRookPieceModelRight};
    whiteCastlingParameters.push_back(castlingData);
    }
    whiteKingPieceModel.castlingParameters = whiteCastlingParameters;
    }
    {
    std::vector <castlingInformation> blackCastlingParameters;
    {
    std::vector <chessPosition> rookPositionsToCheck = {{0,4},{0,3}};
    std::vector <chessPosition> positionsToClear = {{0,3},{0,2},{0,1}};
    chessPosition positionToMoveKingTo = {0,2};
    chessPosition positionToMoveCastilingPieceTo = {0,3};
    chessPosition positionOfCastlingPiece = {0,0};
    castlingInformation castlingData = {rookPositionsToCheck,positionsToClear,positionToMoveKingTo,
    positionToMoveCastilingPieceTo, positionOfCastlingPiece, &whiteRookPieceModelLeft};
    blackCastlingParameters.push_back(castlingData);
    }
    {
    std::vector <chessPosition> rookPositionsToCheck = {{0,4},{0,5}};
    std::vector <chessPosition> positionsToClear = {{0,5},{0,6}};
    chessPosition positionToMoveKingTo = {0,6};
    chessPosition positionToMoveCastilingPieceTo = {0,5};
    chessPosition positionOfCastlingPiece = {0,7};
    castlingInformation castlingData = {rookPositionsToCheck,positionsToClear,positionToMoveKingTo,
    positionToMoveCastilingPieceTo, positionOfCastlingPiece, &whiteRookPieceModelRight};
    blackCastlingParameters.push_back(castlingData);
    }
    blackKingPieceModel.castlingParameters = blackCastlingParameters;
    }
}

void setBlackKingMetaData(chessWidget *chesswidget, chessModel* chessmodel)
{
    {
    std::vector <castlingInformation> blackCastlingParameters;
    {
    std::vector <chessPosition> rookPositionsToCheck = {{7,4},{7,3}};
    std::vector <chessPosition> positionsToClear = {{7,3},{7,2},{7,1}};
    chessPosition positionToMoveKingTo = {7,2};
    chessPosition positionToMoveCastilingPieceTo = {7,3};
    chessPosition positionOfCastlingPiece = {7,0};
    castlingInformation castlingData = {rookPositionsToCheck,positionsToClear,positionToMoveKingTo,
    positionToMoveCastilingPieceTo, positionOfCastlingPiece, &whiteRookPieceModelLeft};
    blackCastlingParameters.push_back(castlingData);
    }
    {
    std::vector <chessPosition> rookPositionsToCheck = {{7,4},{7,5}};
    std::vector <chessPosition> positionsToClear = {{7,5},{7,6}};
    chessPosition positionToMoveKingTo = {7,6};
    chessPosition positionToMoveCastilingPieceTo = {7,5};
    chessPosition positionOfCastlingPiece = {7,7};
    castlingInformation castlingData = {rookPositionsToCheck,positionsToClear,positionToMoveKingTo,
    positionToMoveCastilingPieceTo, positionOfCastlingPiece, &whiteRookPieceModelRight};
    blackCastlingParameters.push_back(castlingData);
    }
    blackKingPieceModel.castlingParameters = blackCastlingParameters;
    }
    {
    std::vector <castlingInformation> whiteCastlingParameters;
    {
    std::vector <chessPosition> rookPositionsToCheck = {{0,4},{0,3}};
    std::vector <chessPosition> positionsToClear = {{0,3},{0,2},{0,1}};
    chessPosition positionToMoveKingTo = {0,2};
    chessPosition positionToMoveCastilingPieceTo = {0,3};
    chessPosition positionOfCastlingPiece = {0,0};
    castlingInformation castlingData = {rookPositionsToCheck,positionsToClear,positionToMoveKingTo,
    positionToMoveCastilingPieceTo, positionOfCastlingPiece, &whiteRookPieceModelLeft};
    whiteCastlingParameters.push_back(castlingData);
    }
    {
    std::vector <chessPosition> rookPositionsToCheck = {{0,4},{0,5}};
    std::vector <chessPosition> positionsToClear = {{0,5},{0,6}};
    chessPosition positionToMoveKingTo = {0,6};
    chessPosition positionToMoveCastilingPieceTo = {0,5};
    chessPosition positionOfCastlingPiece = {0,7};
    castlingInformation castlingData = {rookPositionsToCheck,positionsToClear,positionToMoveKingTo,
    positionToMoveCastilingPieceTo, positionOfCastlingPiece, &whiteRookPieceModelRight};
    whiteCastlingParameters.push_back(castlingData);
    }
    whiteKingPieceModel.castlingParameters = whiteCastlingParameters;
    }
}

const std::vector <mapValue> whiteMapValue 
{
    {{0,0},&blackRookPieceModelLeft,chessWidget::blackQueenRook},
    {{0,1},&blackKnightPieceModel,chessWidget::blackQueenKnight},
    {{0,2},&blackBishopPieceModel,chessWidget::blackQueenBishop},
    {{0,3},&blackQueenPieceModel,chessWidget::blackQueen},
    {{0,4},&blackKingPieceModel,chessWidget::blackKing},
    {{0,5},&blackBishopPieceModel,chessWidget::blackKingBishop},
    {{0,6},&blackKnightPieceModel,chessWidget::blackKingKnight},
    {{0,7},&blackRookPieceModelRight,chessWidget::blackKingRook},
    {{1,0},&blackPawnPieceModel,chessWidget::blackAPawn},
    {{1,1},&blackPawnPieceModel,chessWidget::blackBPawn},
    {{1,2},&blackPawnPieceModel,chessWidget::blackCPawn},
    {{1,3},&blackPawnPieceModel,chessWidget::blackDPawn},
    {{1,4},&blackPawnPieceModel,chessWidget::blackEPawn},
    {{1,5},&blackPawnPieceModel,chessWidget::blackFPawn},
    {{1,6},&blackPawnPieceModel,chessWidget::blackGPawn},
    {{1,7},&blackPawnPieceModel,chessWidget::blackHPawn},
    {{7,0},&whiteRookPieceModelLeft,chessWidget::whiteQueenRook},
    {{7,1},&whiteKnightPieceModel,chessWidget::whiteQueenKnight},
    {{7,2},&whiteBishopPieceModel,chessWidget::whiteQueenBishop},
    {{7,3},&whiteQueenPieceModel,chessWidget::whiteQueen},
    {{7,4},&whiteKingPieceModel,chessWidget::whiteKing},
    {{7,5},&whiteBishopPieceModel,chessWidget::whiteKingBishop},
    {{7,6},&whiteKnightPieceModel,chessWidget::whiteKingKnight},
    {{7,7},&whiteRookPieceModelRight,chessWidget::whiteKingRook},
    {{6,0},&whitePawnPieceModel,chessWidget::whiteAPawn},
    {{6,1},&whitePawnPieceModel,chessWidget::whiteBPawn},
    {{6,2},&whitePawnPieceModel,chessWidget::whiteCPawn},
    {{6,3},&whitePawnPieceModel,chessWidget::whiteDPawn},
    {{6,4},&whitePawnPieceModel,chessWidget::whiteEPawn},
    {{6,5},&whitePawnPieceModel,chessWidget::whiteFPawn},
    {{6,6},&whitePawnPieceModel,chessWidget::whiteGPawn},
    {{6,7},&whitePawnPieceModel,chessWidget::whiteHPawn}
};

const std::vector<void (*)(chessWidget *chesswidget, chessModel* chessmodel)> whiteMapFunctions
{
    (*setWhitePawnMetaData),
    (*setWhiteKingMetaData)
};

const std::vector <mapValue> blackMapValue 
{
    {{7,7},&blackRookPieceModelRight,chessWidget::blackQueenRook},
    {{7,6},&blackKnightPieceModel,chessWidget::blackQueenKnight},
    {{7,5},&blackBishopPieceModel,chessWidget::blackQueenBishop},
    {{7,4},&blackQueenPieceModel,chessWidget::blackQueen},
    {{7,3},&blackKingPieceModel,chessWidget::blackKing},
    {{7,2},&blackBishopPieceModel,chessWidget::blackKingBishop},
    {{7,1},&blackKnightPieceModel,chessWidget::blackKingKnight},
    {{7,0},&blackRookPieceModelLeft,chessWidget::blackKingRook},
    {{6,7},&blackPawnPieceModel,chessWidget::blackAPawn},
    {{6,6},&blackPawnPieceModel,chessWidget::blackBPawn},
    {{6,5},&blackPawnPieceModel,chessWidget::blackCPawn},
    {{6,4},&blackPawnPieceModel,chessWidget::blackDPawn},
    {{6,3},&blackPawnPieceModel,chessWidget::blackEPawn},
    {{6,2},&blackPawnPieceModel,chessWidget::blackFPawn},
    {{6,1},&blackPawnPieceModel,chessWidget::blackGPawn},
    {{6,0},&blackPawnPieceModel,chessWidget::blackHPawn},
    {{0,7},&whiteRookPieceModelRight,chessWidget::whiteQueenRook},
    {{0,6},&whiteKnightPieceModel,chessWidget::whiteQueenKnight},
    {{0,5},&whiteBishopPieceModel,chessWidget::whiteQueenBishop},
    {{0,4},&whiteQueenPieceModel,chessWidget::whiteQueen},
    {{0,3},&whiteKingPieceModel,chessWidget::whiteKing},
    {{0,2},&whiteBishopPieceModel,chessWidget::whiteKingBishop},
    {{0,1},&whiteKnightPieceModel,chessWidget::whiteKingKnight},
    {{0,0},&whiteRookPieceModelLeft,chessWidget::whiteKingRook},
    {{1,7},&whitePawnPieceModel,chessWidget::whiteAPawn},
    {{1,6},&whitePawnPieceModel,chessWidget::whiteBPawn},
    {{1,5},&whitePawnPieceModel,chessWidget::whiteCPawn},
    {{1,4},&whitePawnPieceModel,chessWidget::whiteDPawn},
    {{1,3},&whitePawnPieceModel,chessWidget::whiteEPawn},
    {{1,2},&whitePawnPieceModel,chessWidget::whiteFPawn},
    {{1,1},&whitePawnPieceModel,chessWidget::whiteGPawn},
    {{1,0},&whitePawnPieceModel,chessWidget::whiteHPawn}
};

const std::vector<void (*)(chessWidget *chesswidget, chessModel* chessmodel)> blackMapFunctions
{
    (*setBlackPawnMetaData),
    (*setBlackKingMetaData)
};

const boardSetter whiteGameSetter(whiteMapValue,whiteMapFunctions);
const boardSetter blackGameSetter(blackMapValue,blackMapFunctions);
