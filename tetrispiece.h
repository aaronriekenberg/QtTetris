#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include "tetriscoordinate.h"
#include "tetrisconstants.h"
#include <memory>
#include <vector>

class TetrisPiece
{
public:
    TetrisPiece(
            const TetrisCoordinate& centerCoordinate,
            int orientation,
            const std::vector<TetrisCoordinate>& coordinates);

    virtual ~TetrisPiece() = default;

    virtual TetrisConstants::TetrisCellColor color() const = 0;

    const TetrisCoordinate& centerCoordinate() const;

    int centerRow() const;

    int centerColumn() const;

    int orientation() const;

    virtual int numOrientations() const = 0;

    int nextOrientation() const;

    const std::vector<TetrisCoordinate>& coordinates() const;

    virtual std::shared_ptr<TetrisPiece>
    makeTetrisPiece(const TetrisCoordinate& centerCoordinate,
                    int orientation) const = 0;

    std::shared_ptr<TetrisPiece> cloneWithNewCenterCoordinate(
            const TetrisCoordinate& newCenterCoordinate) const;

    std::shared_ptr<TetrisPiece> cloneWithNewCenterRow(
            int newCenterRow) const;

    std::shared_ptr<TetrisPiece> cloneWithNewCenterColumn(
            int newCenterColumn) const;

    std::shared_ptr<TetrisPiece> cloneWithNextOrientation() const;

private:
    TetrisCoordinate m_centerCoordinate;

    int m_orientation;

    std::vector<TetrisCoordinate> m_coordinates;

};

#endif // TETRISPIECE_H
