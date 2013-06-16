#include "tetriscoordinate.h"
#include "tetrisconstants.h"
#include <boost/functional/hash.hpp>

TetrisCoordinate::TetrisCoordinate(int row, int column) :
    m_row(row),
    m_column(column)
{

}

int TetrisCoordinate::row() const
{
    return m_row;
}

int TetrisCoordinate::column() const
{
    return m_column;
}

bool TetrisCoordinate::isValid() const
{
    return ((m_row >= 0) && (m_row < TetrisConstants::NUM_ROWS) &&
            (m_column >= 0) && (m_column < TetrisConstants::NUM_COLUMNS));
}

bool TetrisCoordinate::operator<(const TetrisCoordinate& rhs) const
{
    return ((m_row < rhs.m_row) ||
            ((m_row == rhs.m_row) &&
             (m_column < rhs.m_column)));
}

bool TetrisCoordinate::operator==(const TetrisCoordinate& rhs) const
{
    return ((m_row == rhs.m_row) &&
            (m_column == rhs.m_column));
}

TetrisCoordinate TetrisCoordinate::plusRows(int rows) const
{
    return TetrisCoordinate(m_row + rows, m_column);
}

TetrisCoordinate TetrisCoordinate::plusColumns(int columns) const
{
    return TetrisCoordinate(m_row, m_column + columns);
}

TetrisCoordinate TetrisCoordinate::plusRowsAndColumns(int rows, int columns) const
{
    return TetrisCoordinate(m_row + rows, m_column + columns);
}

size_t hash_value(const TetrisCoordinate& tetrisCoordinate)
{
    size_t seed = 0;
    boost::hash_combine(seed, tetrisCoordinate.row());
    boost::hash_combine(seed, tetrisCoordinate.column());
    return seed;
}

std::ostream& operator<<(std::ostream& stream, const TetrisCoordinate& tetrisCoordinate)
{
    stream << "TetrisCoordinate [";
    stream << "row=" << tetrisCoordinate.row();
    stream << ",column=" << tetrisCoordinate.column();
    stream << "]";
    return stream;
}
