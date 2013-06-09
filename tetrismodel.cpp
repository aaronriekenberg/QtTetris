#include "tetrismodel.h"
#include <iostream>

namespace
{

class DeferPublish
{
public:
    DeferPublish(int& deferPublishCount) :
        m_needToResume(true),
        m_deferPublishCount(deferPublishCount)
    {
        ++m_deferPublishCount;
    }

    ~DeferPublish()
    {
        resume();
    }

    void resume()
    {
        if (m_needToResume)
        {
            --m_deferPublishCount;
            m_needToResume = false;
        }
    }


private:
    bool m_needToResume;

    int& m_deferPublishCount;
};

}

TetrisModel::TetrisModel(QObject *parent) :
    QObject(parent)
{
    reset();
}

void TetrisModel::reset()
{
    m_pCurrentPiece.reset();

    m_stackCells.reset();

    m_drawableCells.clear();

    m_numLines = 0;

    m_paused = false;

    m_gameOver = false;

    m_deferPublishCount = 0;
}

const std::map<TetrisCoordinate, TetrisConstants::TetrisCellColor>&
TetrisModel::drawableCells() const
{
    return m_drawableCells;
}

void TetrisModel::periodicUpdate()
{
    if (gameRunning())
    {
        DeferPublish deferPublish(m_deferPublishCount);
        if (m_pCurrentPiece)
        {
            moveCurrentPieceDown();
        }
        else
        {
            addNewPiece();
        }
        deferPublish.resume();
        publishTetrisModelEvent();
    }
}

void TetrisModel::moveCurrentPieceDown()
{
    if (gameRunning() && m_pCurrentPiece)
    {
        boost::shared_ptr<TetrisPiece> pCurrentPieceMoved =
                m_pCurrentPiece->cloneWithNewCenterRow(
                    m_pCurrentPiece->centerRow() + 1);
        if (isPieceLocationValid(*pCurrentPieceMoved))
        {
            m_pCurrentPiece = pCurrentPieceMoved;
        }
        else
        {
            addCurrentPieceToStack();
            m_pCurrentPiece.reset();
        }
        publishTetrisModelEvent();
    }
}

void TetrisModel::dropCurrentPiece()
{
    if (gameRunning())
    {
        DeferPublish deferPublish(m_deferPublishCount);
        while (m_pCurrentPiece)
        {
            moveCurrentPieceDown();
        }
        deferPublish.resume();
        publishTetrisModelEvent();
    }
}

void TetrisModel::moveCurrentPieceLeft()
{
    if (gameRunning() && m_pCurrentPiece)
    {
        boost::shared_ptr<TetrisPiece> pCurrentPieceMoved =
                m_pCurrentPiece->cloneWithNewCenterColumn(
                    m_pCurrentPiece->centerColumn() - 1);
        if (isPieceLocationValid(*pCurrentPieceMoved))
        {
            m_pCurrentPiece = pCurrentPieceMoved;
            publishTetrisModelEvent();
        }
    }
}

void TetrisModel::moveCurrentPieceRight()
{
    if (gameRunning() && m_pCurrentPiece)
    {
        boost::shared_ptr<TetrisPiece> pCurrentPieceMoved =
                m_pCurrentPiece->cloneWithNewCenterColumn(
                    m_pCurrentPiece->centerColumn() + 1);
        if (isPieceLocationValid(*pCurrentPieceMoved))
        {
            m_pCurrentPiece = pCurrentPieceMoved;
            publishTetrisModelEvent();
        }
    }
}

void TetrisModel::rotateCurrentPiece()
{
    if (gameRunning() && m_pCurrentPiece)
    {
        boost::shared_ptr<TetrisPiece> pCurrentPieceRotated =
                m_pCurrentPiece->cloneWithNextOrientation();
        if (isPieceLocationValid(*pCurrentPieceRotated))
        {
            m_pCurrentPiece = pCurrentPieceRotated;
            publishTetrisModelEvent();
        }
    }
}

void TetrisModel::togglePause()
{
    m_paused = !m_paused;
    publishTetrisModelEvent();
}

bool TetrisModel::gameRunning() const
{
    return ((!m_gameOver) && (!m_paused));
}

bool TetrisModel::gameOver() const
{
    return m_gameOver;
}

bool TetrisModel::paused() const
{
    return m_paused;
}

int TetrisModel::numLines() const
{
    return m_numLines;
}

void TetrisModel::addNewPiece()
{
    boost::shared_ptr<TetrisPiece> pNewPiece =
            m_pieceFactory.createRandomTetrisPiece();
    if (isPieceLocationValid(*pNewPiece))
    {
        m_pCurrentPiece = pNewPiece;
    }
    else
    {
        m_pCurrentPiece.reset();
        m_gameOver = true;
    }
}

void TetrisModel::addCurrentPieceToStack()
{
    if (m_pCurrentPiece)
    {
        std::vector<TetrisCoordinate>::const_iterator i;
        for (i = m_pCurrentPiece->coordinates().begin();
             i != m_pCurrentPiece->coordinates().end();
             ++i)
        {
            const TetrisCoordinate& coordinate = *i;
            m_stackCells.set(coordinate, m_pCurrentPiece->color());
        }
        handleFilledStackRows();
    }
}

void TetrisModel::handleFilledStackRows()
{
    int row = TetrisConstants::NUM_ROWS - 1;
    while (row >= 0)
    {
        if (m_stackCells.rowIsFull(row))
        {
            m_stackCells.removeRow(row);
            ++m_numLines;
        }
        else
        {
            row -= 1;
        }
    }
}

bool TetrisModel::isPieceLocationValid(const TetrisPiece& tetrisPiece)
{
    std::vector<TetrisCoordinate>::const_iterator i;
    for (i = tetrisPiece.coordinates().begin();
         i != tetrisPiece.coordinates().end();
         ++i)
    {
        const TetrisCoordinate& coordinate = *i;
        if (!coordinate.isValid())
        {
            return false;
        }
        if (m_stackCells.get(coordinate) != TetrisConstants::CELL_NOT_PRESENT)
        {
            return false;
        }
    }
    return true;
}

void TetrisModel::updateDrawableCells()
{
    m_drawableCells.clear();

    if (m_pCurrentPiece)
    {
        std::vector<TetrisCoordinate>::const_iterator i;
        for (i = m_pCurrentPiece->coordinates().begin();
             i != m_pCurrentPiece->coordinates().end();
             ++i)
        {
            const TetrisCoordinate& coordinate = *i;
            m_drawableCells[coordinate] = m_pCurrentPiece->color();
        }
    }

    for (int row = 0; row < TetrisConstants::NUM_ROWS; ++row)
    {
        for (int column = 0; column < TetrisConstants::NUM_COLUMNS; ++column)
        {
            TetrisCoordinate coordinate(row, column);
            TetrisConstants::TetrisCellColor cellColor = m_stackCells.get(coordinate);
            if (cellColor != TetrisConstants::CELL_NOT_PRESENT)
            {
                m_drawableCells[coordinate] = cellColor;
            }
        }
    }
}

void TetrisModel::publishTetrisModelEvent()
{
    if (m_deferPublishCount == 0)
    {
        updateDrawableCells();
        emit modelUpdated();
    }
}
