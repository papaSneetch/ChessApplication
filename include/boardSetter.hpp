#ifndef BOARDSETTER_HPP
#define BOARDSETTER_HPP

#include "view.hpp"
#include "model.hpp"

using namespace chessModelInformation;

namespace setUpBoard
{

 struct mapValue
    {
        chessPosition position;
        chessPieceModel *chessPieceModelMapPointer;
        chessWidget::chessPiecesNames chessPieceMapPointer;
    };

} // namespace setUpBoard

using namespace setUpBoard;


struct boardSetter
{
    std::vector<mapValue> boardSetterData;

    boardSetter(){};

    boardSetter(std::vector<mapValue> data) : boardSetterData(data){};

    void setUpGame(chessWidget *chesswidget, chessModel *chessmodel) const
    {
        for (int i = 0; i < boardSetterData.size(); i++)
        {
            chesswidget->placeChessPieceOnSquare(boardSetterData[i].chessPieceMapPointer,
                                                 boardSetterData[i].position.row, boardSetterData[i].position.collumm);
            chessmodel->setChessPiece(boardSetterData[i].chessPieceModelMapPointer, boardSetterData[i].position);
        }
    }
};

extern const boardSetter whiteGameSetter;
extern const boardSetter blackGameSetter;

#endif