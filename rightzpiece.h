#ifndef RIGHTZPIECE_H
#define RIGHTZPIECE_H

#include "abstracttetrispiece.h"

class RightZPiece : public AbstractTetrisPiece<RightZPiece>
{
public:
    RightZPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual TetrisConstants::TetrisCellColor color() const override;

    virtual int numOrientations() const override;

};

#endif // RIGHTZPIECE_H
