#include <QtGlobal>
#include <QTime>
#include "leftlpiece.h"
#include "leftzpiece.h"
#include "linepiece.h"
#include "rightlpiece.h"
#include "rightzpiece.h"
#include "squarepiece.h"
#include "tetrispiecefactory.h"
#include "tpiece.h"

TetrisPieceFactory::TetrisPieceFactory()
{
    qsrand(QTime::currentTime().msec());

    TetrisCoordinate centerCoordinate(
                0, (TetrisConstants::NUM_COLUMNS / 2) - 1);

    m_pieces.push_back(
                boost::shared_ptr<TetrisPiece>(
                    new SquarePiece(centerCoordinate)));
    m_pieces.push_back(
                boost::shared_ptr<TetrisPiece>(
                    new LeftLPiece(centerCoordinate)));
    m_pieces.push_back(
                boost::shared_ptr<TetrisPiece>(
                    new RightLPiece(centerCoordinate)));
    m_pieces.push_back(
                boost::shared_ptr<TetrisPiece>(
                    new LinePiece(centerCoordinate)));
    m_pieces.push_back(
                boost::shared_ptr<TetrisPiece>(
                    new TPiece(centerCoordinate)));
    m_pieces.push_back(
                boost::shared_ptr<TetrisPiece>(
                    new LeftZPiece(centerCoordinate)));
    m_pieces.push_back(
                boost::shared_ptr<TetrisPiece>(
                    new RightZPiece(centerCoordinate)));
}

boost::shared_ptr<TetrisPiece> TetrisPieceFactory::createRandomTetrisPiece()
{
    const int randomIndex = qrand() % m_pieces.size();
    return m_pieces.at(randomIndex);
}
