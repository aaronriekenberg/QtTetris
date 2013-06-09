#ifndef LEFTLPIECE_H
#define LEFTLPIECE_H

#include "tetrispiece.h"

class LeftLPiece : public TetrisPiece
{
public:
    LeftLPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~LeftLPiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const;
};

#endif // LEFTLPIECE_H
