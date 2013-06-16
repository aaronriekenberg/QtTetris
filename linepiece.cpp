#include "linepiece.h"

namespace
{

std::vector<TetrisCoordinate> buildCoordinates(
        const TetrisCoordinate& centerCoordinate, int orientation)
{
    switch (orientation)
    {
    case 0:
        return { centerCoordinate, centerCoordinate.plusRows(1),
                 centerCoordinate.plusRows(2), centerCoordinate.plusRows(3) };
    case 1:
        return { centerCoordinate, centerCoordinate.plusColumns(1),
                 centerCoordinate.plusColumns(2), centerCoordinate.plusColumns(3) };
    case 2:
        return { centerCoordinate, centerCoordinate.plusRows(-1),
                 centerCoordinate.plusRows(-2), centerCoordinate.plusRows(-3) };
    default:
        return { centerCoordinate, centerCoordinate.plusColumns(-1),
                 centerCoordinate.plusColumns(-2), centerCoordinate.plusColumns(-3) };
    }
}

}

LinePiece::LinePiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    AbstractTetrisPiece(
        centerCoordinate, orientation,
        buildCoordinates(centerCoordinate, orientation))
{

}

TetrisConstants::TetrisCellColor LinePiece::color() const
{
    return TetrisConstants::CELL_RED;
}

int LinePiece::numOrientations() const
{
    return 4;
}
