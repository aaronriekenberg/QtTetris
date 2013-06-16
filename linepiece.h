#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "abstracttetrispiece.h"

class LinePiece : public AbstractTetrisPiece<LinePiece>
{
public:
    LinePiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

};

#endif // LINEPIECE_H
