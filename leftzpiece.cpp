#include "leftzpiece.h"

namespace
{

std::vector<TetrisCoordinate> buildCoordinates(
        const TetrisCoordinate& centerCoordinate, int orientation)
{
    std::vector<TetrisCoordinate> coordinates;
    coordinates.reserve(4);

    switch (orientation)
    {
    case 0:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusColumns(-1));
        coordinates.push_back(centerCoordinate.plusRows(1));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(1, 1));
        break;
    default:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusRows(1));
        coordinates.push_back(centerCoordinate.plusColumns(1));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(-1, 1));
        break;
    }

    return coordinates;
}

}

LeftZPiece::LeftZPiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    AbstractTetrisPiece(
        centerCoordinate, orientation,
        buildCoordinates(centerCoordinate, orientation))
{

}

LeftZPiece::~LeftZPiece()
{

}

TetrisConstants::TetrisCellColor LeftZPiece::color() const
{
    return TetrisConstants::CELL_YELLOW;
}

int LeftZPiece::numOrientations() const
{
    return 2;
}
