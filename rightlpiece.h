#ifndef RIGHTLPIECE_H
#define RIGHTLPIECE_H

#include "tetrispiece.h"

class RightLPiece : public TetrisPiece
{
public:
    RightLPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~RightLPiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const;
};

#endif // RIGHTLPIECE_H
