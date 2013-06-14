#ifndef RIGHTZPIECE_H
#define RIGHTZPIECE_H

#include "abstracttetrispiece.h"

class RightZPiece : public AbstractTetrisPiece<RightZPiece>
{
public:
    RightZPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~RightZPiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

};

#endif // RIGHTZPIECE_H
