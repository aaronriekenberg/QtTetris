#ifndef SQUAREPIECE_H
#define SQUAREPIECE_H

#include "tetrispiece.h"

class SquarePiece : public TetrisPiece
{
public:
    SquarePiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~SquarePiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const;
};

#endif // SQUAREPIECE_H
