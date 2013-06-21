#ifndef ABSTRACTTETRISPIECE_H
#define ABSTRACTTETRISPIECE_H

#include "tetrispiece.h"

template <typename T>
class AbstractTetrisPiece : public TetrisPiece
{
public:
    AbstractTetrisPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation,
            std::vector<TetrisCoordinate>&& coordinates) :
        TetrisPiece(centerCoordinate,
                    orientation,
                    std::move(coordinates))
    {

    }

    virtual std::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const override
    {
        return std::shared_ptr<TetrisPiece>(
                    new T(centerCoordinate, orientation));
    }

};

#endif // ABSTRACTTETRISPIECE_H
