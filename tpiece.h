#ifndef TPIECE_H
#define TPIECE_H

#include "abstracttetrispiece.h"

class TPiece : public AbstractTetrisPiece<TPiece>
{
public:
    TPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

};

#endif // TPIECE_H
