#ifndef TETRISMODEL_H
#define TETRISMODEL_H

#include <QObject>
#include <boost/functional/hash.hpp>
#include <memory>
#include <unordered_map>
#include "tetrispiece.h"
#include "tetrispiecefactory.h"
#include "tetrisstackcells.h"

class TetrisModel : public QObject
{
    Q_OBJECT
public:
    explicit TetrisModel(QObject *parent = 0);

    void reset();

    typedef std::unordered_map<
        TetrisCoordinate,
        TetrisConstants::TetrisCellColor,
        boost::hash<TetrisCoordinate>> DrawableCellsMap_t;

    enum UpdatedStatus_t
    {
        UPDATED,
        NOT_UPDATED
    };

    const DrawableCellsMap_t& drawableStackCells() const;

    UpdatedStatus_t stackCellsUpdated() const;

    const DrawableCellsMap_t& drawableCurrentPieceCells() const;

    UpdatedStatus_t currentPieceUpdated() const;

    void moveCurrentPieceDown();

    void dropCurrentPiece();

    void moveCurrentPieceLeft();

    void moveCurrentPieceRight();

    void rotateCurrentPiece();

    void togglePause();

    bool gameRunning() const;

    bool gameOver() const;

    bool paused() const;

    int numLines() const;
    
signals:
    void modelUpdated(
            TetrisModel::UpdatedStatus_t stackCellsUpdated,
            TetrisModel::UpdatedStatus_t currentPieceUpdated);

public slots:
    void periodicUpdate();

private:
    TetrisModel(const TetrisModel& rhs) = delete;

    TetrisModel& operator=(const TetrisModel& rhs) = delete;

    void addNewPiece();

    void setCurrentPiece(std::shared_ptr<TetrisPiece> pCurrentPiece);

    void clearCurrentPiece();

    void addCurrentPieceToStack();

    void handleFilledStackRows();

    bool isPieceLocationValid(const TetrisPiece& tetrisPiece) const;

    void updateDrawableCells();

    void publishTetrisModelEvent();

    TetrisPieceFactory m_pieceFactory;

    TetrisStackCells m_stackCells;

    std::shared_ptr<TetrisPiece> m_pCurrentPiece;

    DrawableCellsMap_t m_drawableStackCells;

    UpdatedStatus_t m_stackCellsUpdated = UPDATED;

    DrawableCellsMap_t m_drawableCurrentPieceCells;

    UpdatedStatus_t m_currentPieceUpdated = UPDATED;

    int m_numLines = 0;

    bool m_paused = false;

    bool m_gameOver = false;

    int m_deferPublishCount = 0;
    
};

#endif // TETRISMODEL_H
