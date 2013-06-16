#include "tpiece.h"

namespace
{

std::vector<TetrisCoordinate> buildCoordinates(
        const TetrisCoordinate& centerCoordinate, int orientation)
{
    switch (orientation)
    {
    case 0:
        return { centerCoordinate, centerCoordinate.plusColumns(1),
                 centerCoordinate.plusColumns(-1), centerCoordinate.plusRows(1) };
    case 1:
        return { centerCoordinate.plusRows(-1), centerCoordinate,
                 centerCoordinate.plusRows(1), centerCoordinate.plusColumns(1) };
    case 2:
        return { centerCoordinate, centerCoordinate.plusColumns(1),
                 centerCoordinate.plusColumns(-1), centerCoordinate.plusRows(-1) };
    default:
        return { centerCoordinate.plusRows(-1), centerCoordinate,
                 centerCoordinate.plusRows(1), centerCoordinate.plusColumns(-1) };
    }
}

}

TPiece::TPiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    AbstractTetrisPiece(
        centerCoordinate, orientation,
        buildCoordinates(centerCoordinate, orientation))
{

}

TetrisConstants::TetrisCellColor TPiece::color() const
{
    return TetrisConstants::CELL_CYAN;
}

int TPiece::numOrientations() const
{
    return 4;
}
