#ifndef TETRISCONSTANTS_H
#define TETRISCONSTANTS_H

class TetrisConstants
{
public:
    static const int NUM_ROWS;

    static const int NUM_COLUMNS;

    enum TetrisCellColor
    {
        CELL_NOT_PRESENT,
        CELL_RED,
        CELL_GREEN,
        CELL_LIGHTGRAY,
        CELL_MAGENTA,
        CELL_CYAN,
        CELL_YELLOW,
        CELL_BLUE
    };

private:
    TetrisConstants() = delete;

    ~TetrisConstants() = delete;
};

#endif // TETRISCONSTANTS_H
