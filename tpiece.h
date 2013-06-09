#ifndef TPIECE_H
#define TPIECE_H

#include "tetrispiece.h"

class TPiece : public TetrisPiece
{
public:
    TPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~TPiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const;
};

#endif // TPIECE_H
