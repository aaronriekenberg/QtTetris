#ifndef RIGHTZPIECE_H
#define RIGHTZPIECE_H

#include "tetrispiece.h"

class RightZPiece : public TetrisPiece
{
public:
    RightZPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~RightZPiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const;
};

#endif // RIGHTZPIECE_H
