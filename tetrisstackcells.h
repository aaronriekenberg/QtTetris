#ifndef TETRISSTACKCELLS_H
#define TETRISSTACKCELLS_H

#include "tetrisconstants.h"
#include "tetriscoordinate.h"
#include <vector>

class TetrisStackCells
{
public:
    TetrisStackCells();

    void reset();

    TetrisConstants::TetrisCellColor
    get(const TetrisCoordinate& tetrisCoordinate) const;

    void set(const TetrisCoordinate& tetrisCoordinate,
             TetrisConstants::TetrisCellColor color);

    bool rowIsFull(int row) const;

    void removeRow(int row);

private:
    std::vector<std::vector<TetrisConstants::TetrisCellColor>> m_stackCells;

};

#endif // TETRISSTACKCELLS_H
