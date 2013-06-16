#ifndef LEFTZPIECE_H
#define LEFTZPIECE_H

#include "abstracttetrispiece.h"

class LeftZPiece : public AbstractTetrisPiece<LeftZPiece>
{
public:
    LeftZPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual TetrisConstants::TetrisCellColor color() const override;

    virtual int numOrientations() const override;

};

#endif // LEFTZPIECE_H
