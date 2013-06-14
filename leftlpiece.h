#ifndef LEFTLPIECE_H
#define LEFTLPIECE_H

#include "abstracttetrispiece.h"

class LeftLPiece : public AbstractTetrisPiece<LeftLPiece>
{
public:
    LeftLPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~LeftLPiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

};

#endif // LEFTLPIECE_H
