#ifndef RIGHTLPIECE_H
#define RIGHTLPIECE_H

#include "abstracttetrispiece.h"

class RightLPiece : public AbstractTetrisPiece<RightLPiece>
{
public:
    RightLPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~RightLPiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

};

#endif // RIGHTLPIECE_H
