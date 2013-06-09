#ifndef TETRISPIECEFACTORY_H
#define TETRISPIECEFACTORY_H

#include <boost/shared_ptr.hpp>
#include "tetrispiece.h"

class TetrisPieceFactory
{
public:
    TetrisPieceFactory();

    boost::shared_ptr<TetrisPiece> createRandomTetrisPiece();

private:
    std::vector<boost::shared_ptr<TetrisPiece> > m_pieces;

};

#endif // TETRISPIECEFACTORY_H
