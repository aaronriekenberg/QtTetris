#ifndef SQUAREPIECE_H
#define SQUAREPIECE_H

#include "abstracttetrispiece.h"

class SquarePiece : public AbstractTetrisPiece<SquarePiece>
{
public:
    SquarePiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

};

#endif // SQUAREPIECE_H
