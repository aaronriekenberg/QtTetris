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

    m_drawableStackCells.clear();

    m_stackCellsUpdated = UPDATED;

    m_drawableCurrentPieceCells.clear();

    m_currentPieceUpdated = UPDATED;

    m_numLines = 0;

    m_paused = false;

    m_gameOver = false;

    m_deferPublishCount = 0;
}

const TetrisModel::DrawableCellsMap_t&
TetrisModel::drawableStackCells() const
{
    return m_drawableStackCells;
}

TetrisModel::UpdatedStatus_t
TetrisModel::stackCellsUpdated() const
{
    return m_stackCellsUpdated;
}


const TetrisModel::DrawableCellsMap_t&
TetrisModel::drawableCurrentPieceCells() const
{
    return m_drawableCurrentPieceCells;
}

TetrisModel::UpdatedStatus_t
TetrisModel::currentPieceUpdated() const
{
    return m_currentPieceUpdated;
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
        auto pCurrentPieceMoved =
                m_pCurrentPiece->cloneWithNewCenterRow(
                    m_pCurrentPiece->centerRow() + 1);
        if (isPieceLocationValid(*pCurrentPieceMoved))
        {
            setCurrentPiece(pCurrentPieceMoved);
        }
        else
        {
            addCurrentPieceToStack();
            clearCurrentPiece();
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
        auto pCurrentPieceMoved =
                m_pCurrentPiece->cloneWithNewCenterColumn(
                    m_pCurrentPiece->centerColumn() - 1);
        if (isPieceLocationValid(*pCurrentPieceMoved))
        {
            setCurrentPiece(pCurrentPieceMoved);
            publishTetrisModelEvent();
        }
    }
}

void TetrisModel::moveCurrentPieceRight()
{
    if (gameRunning() && m_pCurrentPiece)
    {
        auto pCurrentPieceMoved =
                m_pCurrentPiece->cloneWithNewCenterColumn(
                    m_pCurrentPiece->centerColumn() + 1);
        if (isPieceLocationValid(*pCurrentPieceMoved))
        {
            setCurrentPiece(pCurrentPieceMoved);
            publishTetrisModelEvent();
        }
    }
}

void TetrisModel::rotateCurrentPiece()
{
    if (gameRunning() && m_pCurrentPiece)
    {
        std::shared_ptr<TetrisPiece> pCurrentPieceRotated =
                m_pCurrentPiece->cloneWithNextOrientation();
        if (isPieceLocationValid(*pCurrentPieceRotated))
        {
            setCurrentPiece(pCurrentPieceRotated);
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
    auto pNewPiece = m_pieceFactory.createRandomTetrisPiece();
    if (isPieceLocationValid(*pNewPiece))
    {
        setCurrentPiece(pNewPiece);
    }
    else
    {
        clearCurrentPiece();
        m_gameOver = true;
    }
}


void TetrisModel::setCurrentPiece(
        std::shared_ptr<TetrisPiece> pCurrentPiece)
{
    m_pCurrentPiece = pCurrentPiece;
    m_currentPieceUpdated = UPDATED;
}

void TetrisModel::clearCurrentPiece()
{
    m_pCurrentPiece.reset();
    m_currentPieceUpdated = UPDATED;
}

void TetrisModel::addCurrentPieceToStack()
{
    if (m_pCurrentPiece)
    {
        for (auto coordinate : m_pCurrentPiece->coordinates())
        {
            m_stackCells.set(coordinate, m_pCurrentPiece->color());
        }
        handleFilledStackRows();
        m_stackCellsUpdated = UPDATED;
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

bool TetrisModel::isPieceLocationValid(const TetrisPiece& tetrisPiece) const
{
    for (auto coordinate : tetrisPiece.coordinates())
    {
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
    if (m_currentPieceUpdated == UPDATED)
    {
        m_drawableCurrentPieceCells.clear();
        if (m_pCurrentPiece)
        {
            for (auto coordinate : m_pCurrentPiece->coordinates())
            {
                m_drawableCurrentPieceCells[coordinate] = m_pCurrentPiece->color();
            }
        }
    }

    if (m_stackCellsUpdated == UPDATED)
    {
        m_drawableStackCells.clear();
        for (int row = 0; row < TetrisConstants::NUM_ROWS; ++row)
        {
            for (int column = 0; column < TetrisConstants::NUM_COLUMNS; ++column)
            {
                TetrisCoordinate coordinate(row, column);
                TetrisConstants::TetrisCellColor cellColor = m_stackCells.get(coordinate);
                if (cellColor != TetrisConstants::CELL_NOT_PRESENT)
                {
                    m_drawableStackCells[coordinate] = cellColor;
                }
            }
        }
    }
}

void TetrisModel::publishTetrisModelEvent()
{
    if (m_deferPublishCount == 0)
    {
        updateDrawableCells();
        emit modelUpdated(m_stackCellsUpdated, m_currentPieceUpdated);
        m_currentPieceUpdated = NOT_UPDATED;
        m_stackCellsUpdated = NOT_UPDATED;
    }
}
