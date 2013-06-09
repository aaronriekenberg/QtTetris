#include "squarepiece.h"

namespace
{

std::vector<TetrisCoordinate> buildCoordinates(
        const TetrisCoordinate& centerCoordinate)
{
    std::vector<TetrisCoordinate> coordinates;
    coordinates.reserve(4);
    coordinates.push_back(centerCoordinate);
    coordinates.push_back(centerCoordinate.plusRows(1));
    coordinates.push_back(centerCoordinate.plusColumns(1));
    coordinates.push_back(centerCoordinate.plusRowsAndColumns(1, 1));
    return coordinates;
}

}

SquarePiece::SquarePiece(
        const TetrisCoordinate& centerCoordinate,
        int orientation) :
    TetrisPiece(centerCoordinate, orientation,
                buildCoordinates(centerCoordinate))
{

}

SquarePiece::~SquarePiece()
{

}

TetrisConstants::TetrisCellColor SquarePiece::color() const
{
    return TetrisConstants::CELL_GREEN;
}

int SquarePiece::numOrientations() const
{
    return 1;
}

boost::shared_ptr<TetrisPiece>
SquarePiece::makeTetrisPiece(
         const TetrisCoordinate& centerCoordinate,
         int orientation) const
{
    return boost::shared_ptr<TetrisPiece>(
                new SquarePiece(
                    centerCoordinate, orientation));
}