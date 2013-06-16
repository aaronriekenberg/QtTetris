#include "rightzpiece.h"

namespace
{

std::vector<TetrisCoordinate> buildCoordinates(
        const TetrisCoordinate& centerCoordinate, int orientation)
{
    switch (orientation)
    {
    case 0:
        return { centerCoordinate, centerCoordinate.plusColumns(1),
                 centerCoordinate.plusRows(1), centerCoordinate.plusRowsAndColumns(1, -1) };
    default:
        return { centerCoordinate, centerCoordinate.plusRows(-1),
                 centerCoordinate.plusColumns(1), centerCoordinate.plusRowsAndColumns(1, 1) };
    }
}

}

RightZPiece::RightZPiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    AbstractTetrisPiece(
        centerCoordinate, orientation,
        buildCoordinates(centerCoordinate, orientation))
{

}

TetrisConstants::TetrisCellColor RightZPiece::color() const
{
    return TetrisConstants::CELL_BLUE;
}

int RightZPiece::numOrientations() const
{
    return 2;
}
