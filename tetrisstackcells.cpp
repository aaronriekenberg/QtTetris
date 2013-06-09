#include <algorithm>
#include "tetrisstackcells.h"

TetrisStackCells::TetrisStackCells()
{
    reset();
}

void TetrisStackCells::reset()
{
    m_stackCells.clear();
    m_stackCells.reserve(TetrisConstants::NUM_ROWS);
    for (int row = 0; row < TetrisConstants::NUM_ROWS; ++row)
    {
        m_stackCells.push_back(
                    std::vector<TetrisConstants::TetrisCellColor>(
                        TetrisConstants::NUM_COLUMNS, TetrisConstants::CELL_NOT_PRESENT));
    }
}

TetrisConstants::TetrisCellColor
TetrisStackCells::get(
        const TetrisCoordinate& tetrisCoordinate) const
{
    return m_stackCells.at(tetrisCoordinate.row()).
            at(tetrisCoordinate.column());
}

void TetrisStackCells::set(
        const TetrisCoordinate& tetrisCoordinate,
        TetrisConstants::TetrisCellColor color)
{
    m_stackCells.at(tetrisCoordinate.row()).
            at(tetrisCoordinate.column()) = color;
}


bool TetrisStackCells::rowIsFull(int row) const
{
    const std::vector<TetrisConstants::TetrisCellColor>& columnVector =
            m_stackCells.at(row);
    return (std::find(
                columnVector.begin(),
                columnVector.end(),
                TetrisConstants::CELL_NOT_PRESENT) == columnVector.end());
}

void TetrisStackCells::removeRow(int row)
{
    m_stackCells.erase(m_stackCells.begin() + row);
    m_stackCells.insert(
                m_stackCells.begin(),
                std::vector<TetrisConstants::TetrisCellColor>(
                    TetrisConstants::NUM_COLUMNS, TetrisConstants::CELL_NOT_PRESENT));
}
