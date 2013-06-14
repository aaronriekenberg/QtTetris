#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include "tetriscoordinate.h"
#include "tetrisconstants.h"
#include <boost/shared_ptr.hpp>
#include <vector>

class TetrisPiece
{
public:
    TetrisPiece()
    {

    }

    virtual ~TetrisPiece()
    {

    }

    virtual TetrisConstants::TetrisCellColor color() const = 0;

    virtual const TetrisCoordinate& centerCoordinate() const = 0;

    virtual int centerRow() const = 0;

    virtual int centerColumn() const = 0;

    virtual int orientation() const = 0;

    virtual int numOrientations() const = 0;

    virtual int nextOrientation() const = 0;

    virtual const std::vector<TetrisCoordinate>& coordinates() const = 0;

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const = 0;

    virtual boost::shared_ptr<TetrisPiece> cloneWithNewCenterCoordinate(
            const TetrisCoordinate& newCenterCoordinate) const = 0;

    virtual boost::shared_ptr<TetrisPiece> cloneWithNewCenterRow(
            int newCenterRow) const = 0;

    virtual boost::shared_ptr<TetrisPiece> cloneWithNewCenterColumn(
            int newCenterColumn) const = 0;

    virtual boost::shared_ptr<TetrisPiece> cloneWithNextOrientation() const = 0;

};

#endif // TETRISPIECE_H
