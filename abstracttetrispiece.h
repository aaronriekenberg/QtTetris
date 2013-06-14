#ifndef ABSTRACTTETRISPIECE_H
#define ABSTRACTTETRISPIECE_H

#include "tetrispiece.h"

template <typename T>
class AbstractTetrisPiece : public TetrisPiece
{
public:
    AbstractTetrisPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation,
            const std::vector<TetrisCoordinate>& coordinates) :
        m_centerCoordinate(centerCoordinate),
        m_orientation(orientation),
        m_coordinates(coordinates)
    {

    }

    virtual ~AbstractTetrisPiece()
    {

    }

    virtual const TetrisCoordinate& centerCoordinate() const
    {
        return m_centerCoordinate;
    }

    virtual int centerRow() const
    {
        return centerCoordinate().row();
    }

    virtual int centerColumn() const
    {
        return centerCoordinate().column();
    }

    virtual int orientation() const
    {
        return m_orientation;
    }

    virtual int nextOrientation() const
    {
        return ((orientation() + 1) % numOrientations());
    }

    virtual const std::vector<TetrisCoordinate>& coordinates() const
    {
        return m_coordinates;
    }

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const
    {
        return boost::shared_ptr<TetrisPiece>(
                    new T(centerCoordinate, orientation));
    }

    virtual boost::shared_ptr<TetrisPiece> cloneWithNewCenterCoordinate(
            const TetrisCoordinate& newCenterCoordinate) const
    {
        return makeTetrisPiece(newCenterCoordinate, orientation());
    }

    virtual boost::shared_ptr<TetrisPiece> cloneWithNewCenterRow(
            int newCenterRow) const
    {
        return cloneWithNewCenterCoordinate(
                    TetrisCoordinate(newCenterRow, centerColumn()));
    }

    virtual boost::shared_ptr<TetrisPiece> cloneWithNewCenterColumn(
            int newCenterColumn) const
    {
        return cloneWithNewCenterCoordinate(
                    TetrisCoordinate(centerRow(), newCenterColumn));
    }

    virtual boost::shared_ptr<TetrisPiece> cloneWithNextOrientation() const
    {
        return makeTetrisPiece(centerCoordinate(), nextOrientation());
    }

private:
    TetrisCoordinate m_centerCoordinate;

    int m_orientation;

    std::vector<TetrisCoordinate> m_coordinates;

};

#endif // ABSTRACTTETRISPIECE_H
