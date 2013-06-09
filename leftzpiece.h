#ifndef LEFTZPIECE_H
#define LEFTZPIECE_H

#include "tetrispiece.h"

class LeftZPiece : public TetrisPiece
{
public:
    LeftZPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~LeftZPiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const;
};

#endif // LEFTZPIECE_H
