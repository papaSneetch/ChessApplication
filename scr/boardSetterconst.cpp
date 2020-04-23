#include "boardSetter.hpp"

using namespace setUpBoard; 

extern kingPieceModel <2,2> whiteKingPieceModel;
extern kingPieceModel <2,2> blackKingPieceModel;
extern queenPieceModel whiteQueenPieceModel;
extern queenPieceModel blackQueenPieceModel;
extern bishopPieceModel whiteBishopPieceModel;
extern bishopPieceModel blackBishopPieceModel;
extern knightPieceModel whiteKnightPieceModel;
extern knightPieceModel blackKnightPieceModel;
extern rookPieceModel whiteRookPieceModel;
extern rookPieceModel blackRookPieceModel;
extern pawnPieceModel whitePawnPieceModel;
extern pawnPieceModel blackPawnPieceModel;
extern nullPieceModel defaultnullPieceModel;


const std::vector <mapValue> whiteMapValue 
{
    {{0,0},&blackRookPieceModel,chessWidget::blackQueenRook},
    {{0,1},&blackKnightPieceModel,chessWidget::blackQueenKnight},
    {{0,2},&blackBishopPieceModel,chessWidget::blackQueenBishop},
    {{0,3},&blackQueenPieceModel,chessWidget::blackQueen},
    {{0,4},&blackKingPieceModel,chessWidget::blackKing},
    {{0,5},&blackBishopPieceModel,chessWidget::blackKingBishop},
    {{0,6},&blackKnightPieceModel,chessWidget::blackKingKnight},
    {{0,7},&blackRookPieceModel,chessWidget::blackKingRook},
    {{1,0},&blackPawnPieceModel,chessWidget::blackAPawn},
    {{1,1},&blackPawnPieceModel,chessWidget::blackBPawn},
    {{1,2},&blackPawnPieceModel,chessWidget::blackCPawn},
    {{1,3},&blackPawnPieceModel,chessWidget::blackDPawn},
    {{1,4},&blackPawnPieceModel,chessWidget::blackEPawn},
    {{1,5},&blackPawnPieceModel,chessWidget::blackFPawn},
    {{1,6},&blackPawnPieceModel,chessWidget::blackGPawn},
    {{1,7},&blackPawnPieceModel,chessWidget::blackHPawn},
    {{7,0},&whiteRookPieceModel,chessWidget::whiteQueenRook},
    {{7,1},&whiteKnightPieceModel,chessWidget::whiteQueenKnight},
    {{7,2},&whiteBishopPieceModel,chessWidget::whiteQueenBishop},
    {{7,3},&whiteQueenPieceModel,chessWidget::whiteQueen},
    {{7,4},&whiteKingPieceModel,chessWidget::whiteKing},
    {{7,5},&whiteBishopPieceModel,chessWidget::whiteKingBishop},
    {{7,6},&whiteKnightPieceModel,chessWidget::whiteKingKnight},
    {{7,7},&whiteRookPieceModel,chessWidget::whiteKingRook},
    {{6,0},&whitePawnPieceModel,chessWidget::whiteAPawn},
    {{6,1},&whitePawnPieceModel,chessWidget::whiteBPawn},
    {{6,2},&whitePawnPieceModel,chessWidget::whiteCPawn},
    {{6,3},&whitePawnPieceModel,chessWidget::whiteDPawn},
    {{6,4},&whitePawnPieceModel,chessWidget::whiteEPawn},
    {{6,5},&whitePawnPieceModel,chessWidget::whiteFPawn},
    {{6,6},&whitePawnPieceModel,chessWidget::whiteGPawn},
    {{6,7},&whitePawnPieceModel,chessWidget::whiteHPawn}
};

const std::vector <mapValue> blackMapValue 
{
    {{7,7},&blackRookPieceModel,chessWidget::blackQueenRook},
    {{7,6},&blackKnightPieceModel,chessWidget::blackQueenKnight},
    {{7,5},&blackBishopPieceModel,chessWidget::blackQueenBishop},
    {{7,4},&blackQueenPieceModel,chessWidget::blackQueen},
    {{7,3},&blackKingPieceModel,chessWidget::blackKing},
    {{7,2},&blackBishopPieceModel,chessWidget::blackKingBishop},
    {{7,1},&blackKnightPieceModel,chessWidget::blackKingKnight},
    {{7,0},&blackRookPieceModel,chessWidget::blackKingRook},
    {{6,7},&blackPawnPieceModel,chessWidget::blackAPawn},
    {{6,6},&blackPawnPieceModel,chessWidget::blackBPawn},
    {{6,5},&blackPawnPieceModel,chessWidget::blackCPawn},
    {{6,4},&blackPawnPieceModel,chessWidget::blackDPawn},
    {{6,3},&blackPawnPieceModel,chessWidget::blackEPawn},
    {{6,2},&blackPawnPieceModel,chessWidget::blackFPawn},
    {{6,1},&blackPawnPieceModel,chessWidget::blackGPawn},
    {{6,0},&blackPawnPieceModel,chessWidget::blackHPawn},
    {{0,7},&whiteRookPieceModel,chessWidget::whiteQueenRook},
    {{0,6},&whiteKnightPieceModel,chessWidget::whiteQueenKnight},
    {{0,5},&whiteBishopPieceModel,chessWidget::whiteQueenBishop},
    {{0,4},&whiteQueenPieceModel,chessWidget::whiteQueen},
    {{0,3},&whiteKingPieceModel,chessWidget::whiteKing},
    {{0,2},&whiteBishopPieceModel,chessWidget::whiteKingBishop},
    {{0,1},&whiteKnightPieceModel,chessWidget::whiteKingKnight},
    {{0,0},&whiteRookPieceModel,chessWidget::whiteKingRook},
    {{1,7},&whitePawnPieceModel,chessWidget::whiteAPawn},
    {{1,6},&whitePawnPieceModel,chessWidget::whiteBPawn},
    {{1,5},&whitePawnPieceModel,chessWidget::whiteCPawn},
    {{1,4},&whitePawnPieceModel,chessWidget::whiteDPawn},
    {{1,3},&whitePawnPieceModel,chessWidget::whiteEPawn},
    {{1,2},&whitePawnPieceModel,chessWidget::whiteFPawn},
    {{1,1},&whitePawnPieceModel,chessWidget::whiteGPawn},
    {{1,0},&whitePawnPieceModel,chessWidget::whiteHPawn}
};

const boardSetter whiteGameSetter(whiteMapValue);
const boardSetter blackGameSetter(blackMapValue);
