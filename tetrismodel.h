#ifndef TETRISMODEL_H
#define TETRISMODEL_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <map>
#include "tetrispiece.h"
#include "tetrispiecefactory.h"
#include "tetrisstackcells.h"

class TetrisModel : public QObject
{
    Q_OBJECT
public:
    explicit TetrisModel(QObject *parent = 0);

    void reset();

    const std::map<TetrisCoordinate, TetrisConstants::TetrisCellColor>&
    drawableCells() const;

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
    void modelUpdated();

public slots:
    void periodicUpdate();

private:
    TetrisModel(const TetrisModel& rhs);
    TetrisModel& operator=(const TetrisModel& rhs);

    void addNewPiece();

    void addCurrentPieceToStack();

    void handleFilledStackRows();

    bool isPieceLocationValid(const TetrisPiece& tetrisPiece);

    void updateDrawableCells();

    void publishTetrisModelEvent();

    TetrisPieceFactory m_pieceFactory;

    TetrisStackCells m_stackCells;

    boost::shared_ptr<TetrisPiece> m_pCurrentPiece;

    std::map<TetrisCoordinate, TetrisConstants::TetrisCellColor> m_drawableCells;

    int m_numLines;

    bool m_paused;

    bool m_gameOver;

    int m_deferPublishCount;
    
};

#endif // TETRISMODEL_H
