#ifndef LINEPIECE_H
#define LINEPIECE_H

#include "tetrispiece.h"

class LinePiece : public TetrisPiece
{
public:
    LinePiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation = 0);

    virtual ~LinePiece();

    virtual TetrisConstants::TetrisCellColor color() const;

    virtual int numOrientations() const;

    virtual boost::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const;
};

#endif // LINEPIECE_H
