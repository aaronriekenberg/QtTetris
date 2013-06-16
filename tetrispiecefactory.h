#ifndef TETRISPIECEFACTORY_H
#define TETRISPIECEFACTORY_H

#include <memory>
#include "tetrispiece.h"

class TetrisPieceFactory
{
public:
    TetrisPieceFactory();

    std::shared_ptr<TetrisPiece> createRandomTetrisPiece();

private:
    std::vector<std::shared_ptr<TetrisPiece> > m_pieces;

};

#endif // TETRISPIECEFACTORY_H
