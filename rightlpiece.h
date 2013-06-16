#ifndef RIGHTLPIECE_H
#define RIGHTLPIECE_H

#include "abstracttetrispiece.h"

class RightLPiece : public AbstractTetrisPiece<RightLPiece>
{
public:
    RightLPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual TetrisConstants::TetrisCellColor color() const override;

    virtual int numOrientations() const override;

};

#endif // RIGHTLPIECE_H
