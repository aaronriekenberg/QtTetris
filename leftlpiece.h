#ifndef LEFTLPIECE_H
#define LEFTLPIECE_H

#include "abstracttetrispiece.h"

class LeftLPiece : public AbstractTetrisPiece<LeftLPiece>
{
public:
    LeftLPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual TetrisConstants::TetrisCellColor color() const override;

    virtual int numOrientations() const override;

};

#endif // LEFTLPIECE_H
