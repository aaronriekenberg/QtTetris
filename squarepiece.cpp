#include "squarepiece.h"

namespace
{

std::vector<TetrisCoordinate> buildCoordinates(
        const TetrisCoordinate& centerCoordinate)
{
    return { centerCoordinate, centerCoordinate.plusRows(1),
             centerCoordinate.plusColumns(1), centerCoordinate.plusRowsAndColumns(1, 1) };
}

}

SquarePiece::SquarePiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    AbstractTetrisPiece(
        centerCoordinate, orientation,
        buildCoordinates(centerCoordinate))
{

}

TetrisConstants::TetrisCellColor SquarePiece::color() const
{
    return TetrisConstants::CELL_GREEN;
}

int SquarePiece::numOrientations() const
{
    return 1;
}
