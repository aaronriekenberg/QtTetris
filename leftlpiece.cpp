#include "leftlpiece.h"

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
        coordinates.push_back(centerCoordinate.plusRows(1));
        coordinates.push_back(centerCoordinate.plusRows(2));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(2, -1));
        break;
    case 1:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusColumns(1));
        coordinates.push_back(centerCoordinate.plusColumns(2));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(1, 2));
        break;
    case 2:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusRows(-1));
        coordinates.push_back(centerCoordinate.plusRows(-2));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(-2, 1));
        break;
    default:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusColumns(-1));
        coordinates.push_back(centerCoordinate.plusColumns(-2));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(-1, -2));
        break;
    }

    return coordinates;
}

}

LeftLPiece::LeftLPiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    AbstractTetrisPiece(
        centerCoordinate, orientation,
        buildCoordinates(centerCoordinate, orientation))
{

}

LeftLPiece::~LeftLPiece()
{

}

TetrisConstants::TetrisCellColor LeftLPiece::color() const
{
    return TetrisConstants::CELL_LIGHTGRAY;
}

int LeftLPiece::numOrientations() const
{
    return 4;
}
