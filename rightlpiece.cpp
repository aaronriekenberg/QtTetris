#include "rightlpiece.h"

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
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(2, 1));
        break;
    case 1:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusColumns(1));
        coordinates.push_back(centerCoordinate.plusColumns(2));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(-1, 2));
        break;
    case 2:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusRows(-1));
        coordinates.push_back(centerCoordinate.plusRows(-2));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(-2, -1));
        break;
    default:
        coordinates.push_back(centerCoordinate);
        coordinates.push_back(centerCoordinate.plusColumns(-1));
        coordinates.push_back(centerCoordinate.plusColumns(-2));
        coordinates.push_back(centerCoordinate.plusRowsAndColumns(1, -2));
        break;
    }

    return coordinates;
}

}

RightLPiece::RightLPiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    TetrisPiece(centerCoordinate, orientation,
                buildCoordinates(centerCoordinate, orientation))
{

}

RightLPiece::~RightLPiece()
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

boost::shared_ptr<TetrisPiece>
RightLPiece::makeTetrisPiece(
         const TetrisCoordinate& centerCoordinate,
         int orientation) const
{
    return boost::shared_ptr<TetrisPiece>(
                new RightLPiece(
                    centerCoordinate, orientation));
}