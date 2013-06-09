#include "rightzpiece.h"

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
        coordinates.push_back(centerCoordinate.plusRows(1));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(1, -1));
        break;
    default:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusRows(-1));
        coordinates.push_back(centerCoordinate.plusColumns(1));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(1, 1));
        break;
    }

    return coordinates;
}

}

RightZPiece::RightZPiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    TetrisPiece(centerCoordinate, orientation,
                buildCoordinates(centerCoordinate, orientation))
{

}

RightZPiece::~RightZPiece()
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

boost::shared_ptr<TetrisPiece>
RightZPiece::makeTetrisPiece(
         const TetrisCoordinate& centerCoordinate,
         int orientation) const
{
    return boost::shared_ptr<TetrisPiece>(
                new RightZPiece(
                    centerCoordinate, orientation));
}
