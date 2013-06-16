#include "rightlpiece.h"

namespace
{

std::vector<TetrisCoordinate> buildCoordinates(
        const TetrisCoordinate& centerCoordinate, int orientation)
{
    switch (orientation)
    {
    case 0:
        return { centerCoordinate, centerCoordinate.plusRows(1),
                 centerCoordinate.plusRows(2), centerCoordinate.plusRowsAndColumns(2, 1) };
    case 1:
        return { centerCoordinate, centerCoordinate.plusColumns(1),
                 centerCoordinate.plusColumns(2), centerCoordinate.plusRowsAndColumns(-1, 2) };
    case 2:
        return { centerCoordinate, centerCoordinate.plusRows(-1),
                 centerCoordinate.plusRows(-2), centerCoordinate.plusRowsAndColumns(-2, -1) };
    default:
        return { centerCoordinate, centerCoordinate.plusColumns(-1),
                 centerCoordinate.plusColumns(-2), centerCoordinate.plusRowsAndColumns(1, -2) };
    }
}

}

RightLPiece::RightLPiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    AbstractTetrisPiece(
        centerCoordinate, orientation,
        buildCoordinates(centerCoordinate, orientation))
{

}

TetrisConstants::TetrisCellColor RightLPiece::color() const
{
    return TetrisConstants::CELL_MAGENTA;
}

int RightLPiece::numOrientations() const
{
    return 4;
}
