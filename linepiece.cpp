#include "linepiece.h"

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
        coordinates.push_back(centerCoordinate.plusRows(3));
        break;
    case 1:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusColumns(1));
        coordinates.push_back(centerCoordinate.plusColumns(2));
        coordinates.push_back(centerCoordinate.plusColumns(3));
        break;
    case 2:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusRows(-1));
        coordinates.push_back(centerCoordinate.plusRows(-2));
        coordinates.push_back(centerCoordinate.plusRows(-3));
        break;
    default:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusColumns(-1));
        coordinates.push_back(centerCoordinate.plusColumns(-2));
        coordinates.push_back(centerCoordinate.plusColumns(-3));
        break;
    }

    return coordinates;
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

LinePiece::~LinePiece()
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
