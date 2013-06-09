#ifndef TETRISCOORDINATE_H
#define TETRISCOORDINATE_H

#include <iostream>

class TetrisCoordinate
{
public:
    TetrisCoordinate(int row, int column);

    int row() const;

    int column() const;

    bool isValid() const;

    bool operator<(const TetrisCoordinate& rhs) const;

    bool operator==(const TetrisCoordinate& rhs) const;

    TetrisCoordinate plusRows(int rows) const;

    TetrisCoordinate plusColumns(int columns) const;

    TetrisCoordinate plusRowsAndColumns(int rows, int columns) const;

private:
    int m_row;

    int m_column;

};

std::ostream& operator<<(std::ostream& stream, const TetrisCoordinate& tetrisCoordinate);

#endif // TETRISCOORDINATE_H
