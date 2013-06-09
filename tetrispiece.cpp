#include "tetrispiece.h"

TetrisPiece::TetrisPiece(
        TetrisCoordinate centerCoordinate,
        int orientation,
        const std::vector<TetrisCoordinate>& coordinates) :
    m_centerCoordinate(centerCoordinate),
    m_orientation(orientation),
    m_coordinates(coordinates)
{

}

TetrisPiece::~TetrisPiece()
{

}


const TetrisCoordinate&
TetrisPiece::centerCoordinate() const
{
    return m_centerCoordinate;
}

int TetrisPiece::centerRow() const
{
    return centerCoordinate().row();
}

int TetrisPiece::centerColumn() const
{
    return centerCoordinate().column();
}

int TetrisPiece::orientation() const
{
    return m_orientation;
}

int TetrisPiece::nextOrientation() const
{
    return ((orientation() + 1) % numOrientations());
}

const std::vector<TetrisCoordinate>& TetrisPiece::coordinates() const
{
    return m_coordinates;
}

boost::shared_ptr<TetrisPiece>
TetrisPiece::cloneWithNewCenterCoordinate(
        const TetrisCoordinate& newCenterCoordinate) const
{
    return makeTetrisPiece(newCenterCoordinate, orientation());
}

boost::shared_ptr<TetrisPiece>
TetrisPiece::cloneWithNewCenterRow(
        int newCenterRow) const
{
    return cloneWithNewCenterCoordinate(
                TetrisCoordinate(newCenterRow, centerColumn()));
}

boost::shared_ptr<TetrisPiece>
TetrisPiece::cloneWithNewCenterColumn(
        int newCenterColumn) const
{
    return cloneWithNewCenterCoordinate(
                TetrisCoordinate(centerRow(), newCenterColumn));
}

boost::shared_ptr<TetrisPiece>
TetrisPiece::cloneWithNextOrientation() const
{
    return makeTetrisPiece(centerCoordinate(), nextOrientation());
}
