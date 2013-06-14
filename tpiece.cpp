#include "tpiece.h"

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
        coordinates.push_back(centerCoordinate.plusColumns(1));
        coordinates.push_back(centerCoordinate.plusColumns(-1));
        coordinates.push_back(centerCoordinate.plusRows(1));
        break;
    case 1:
        coordinates.push_back(centerCoordinate.plusRows(-1));
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusRows(1));
        coordinates.push_back(centerCoordinate.plusColumns(1));
        break;
    case 2:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusColumns(1));
        coordinates.push_back(centerCoordinate.plusColumns(-1));
        coordinates.push_back(centerCoordinate.plusRows(-1));
        break;
    default:
        coordinates.push_back(centerCoordinate.plusRows(-1));
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusRows(1));
        coordinates.push_back(centerCoordinate.plusColumns(-1));
        break;
    }

    return coordinates;
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

TPiece::~TPiece()
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
