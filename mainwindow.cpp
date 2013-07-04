#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tetrisconstants.h"
#include "tetrismodel.h"
#include <QKeyEvent>
#include <iostream>

namespace
{

void setQWidgetColor(QWidget& widget, const QColor& newColor)
{
    if (newColor != widget.palette().color(widget.backgroundRole()))
    {
        QPalette palette = widget.palette();
        palette.setColor(widget.backgroundRole(), newColor);
        widget.setPalette(palette);
    }
}

QColor tetrisCellColorToQColor(
        TetrisConstants::TetrisCellColor tetrisCellColor)
{
    switch (tetrisCellColor)
    {
    case TetrisConstants::CELL_NOT_PRESENT:
        return QColor(Qt::black);
    case TetrisConstants::CELL_RED:
        return QColor(Qt::red);
    case TetrisConstants::CELL_GREEN:
        return QColor(Qt::green);
    case TetrisConstants::CELL_LIGHTGRAY:
        return QColor(Qt::lightGray);
    case TetrisConstants::CELL_MAGENTA:
        return QColor(Qt::magenta);
    case TetrisConstants::CELL_CYAN:
        return QColor(Qt::cyan);
    case TetrisConstants::CELL_YELLOW:
        return QColor(Qt::yellow);
    case TetrisConstants::CELL_BLUE:
        return QColor(Qt::blue);
    }
    return QColor(Qt::black);
}

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUI(new Ui::MainWindow),
    m_pModel(new TetrisModel),
    m_pTimer(new QTimer)
{
    m_pUI->setupUi(this);

    // Set background to black
    QPalette palette = m_pUI->tetrisFrame->palette();
    palette.setColor(m_pUI->tetrisFrame->backgroundRole(), Qt::black);
    m_pUI->tetrisFrame->setPalette(palette);

    // Set text label color
    palette = m_pUI->tetrisStatusLabel->palette();
    palette.setColor(m_pUI->tetrisStatusLabel->foregroundRole(), Qt::red);
    m_pUI->tetrisStatusLabel->setPalette(palette);

    // Assemble game board as grid of frames that can be colored
    for (int row = 0; row < TetrisConstants::NUM_ROWS; ++row)
    {
        for (int column = 0; column < TetrisConstants::NUM_COLUMNS; ++column)
        {
            QWidget* pWidget = new QWidget;
            palette = pWidget->palette();
            palette.setColor(pWidget->backgroundRole(), Qt::black);
            pWidget->setPalette(palette);
            pWidget->setAutoFillBackground(true);
            m_pUI->tetrisGrid->addWidget(pWidget, row, column);
            TetrisCoordinate coordinate(row, column);
            m_allWidgets[coordinate] = pWidget;
        }
    }


    QObject::connect(m_pTimer, SIGNAL(timeout()), m_pModel, SLOT(periodicUpdate()));
    m_pTimer->start(250);

    QObject::connect(m_pModel,
                     SIGNAL(modelUpdated(TetrisModel::UpdatedStatus_t,
                                         TetrisModel::UpdatedStatus_t)),
                     this,
                     SLOT(modelUpdated(TetrisModel::UpdatedStatus_t,
                                       TetrisModel::UpdatedStatus_t)));
    modelUpdated(TetrisModel::UPDATED, TetrisModel::UPDATED);
}

void MainWindow::modelUpdated(
        TetrisModel::UpdatedStatus_t stackCellsUpdated,
        TetrisModel::UpdatedStatus_t currentPieceUpdated)
{
    std::unordered_map<TetrisCoordinate, QColor,
        boost::hash<TetrisCoordinate>> updatedCellCoordinateToColor;

    if (stackCellsUpdated == TetrisModel::UPDATED)
    {
        for (TetrisCoordinate coordinate : m_stackCellCoordinates)
        {
            updatedCellCoordinateToColor[coordinate] = QColor(Qt::black);
        }
        m_stackCellCoordinates.clear();
    }

    if (currentPieceUpdated == TetrisModel::UPDATED)
    {
        for (TetrisCoordinate coordinate : m_currentPieceCoordinates)
        {
            updatedCellCoordinateToColor[coordinate] = QColor(Qt::black);
        }
        m_currentPieceCoordinates.clear();
    }

    if (stackCellsUpdated == TetrisModel::UPDATED)
    {
        const auto& drawableStackCells = m_pModel->drawableStackCells();
        for (auto drawableEntry : drawableStackCells)
        {
            TetrisCoordinate coordinate = drawableEntry.first;
            updatedCellCoordinateToColor[coordinate] =
                    tetrisCellColorToQColor(drawableEntry.second);
            m_stackCellCoordinates.insert(coordinate);
        }
    }

    if (currentPieceUpdated == TetrisModel::UPDATED)
    {
        const auto& drawableCurrentPieceCells = m_pModel->drawableCurrentPieceCells();
        for (auto drawableEntry : drawableCurrentPieceCells)
        {
            TetrisCoordinate coordinate = drawableEntry.first;
            updatedCellCoordinateToColor[coordinate] =
                    tetrisCellColorToQColor(drawableEntry.second);
            m_currentPieceCoordinates.insert(coordinate);
        }
    }

    for (auto updatedEntry : updatedCellCoordinateToColor)
    {
        TetrisCoordinate coordinate = updatedEntry.first;
        QWidget* pWidget = m_allWidgets[coordinate];
        setQWidgetColor(*pWidget, updatedEntry.second);
    }

    if (m_pModel->gameOver())
    {
        m_pUI->tetrisStatusLabel->setText(
                    QString("Game Over Lines: %1").arg(m_pModel->numLines()));
    }
    else if (m_pModel->paused())
    {
        m_pUI->tetrisStatusLabel->setText(
                    QString("Paused"));
    }
    else
    {
        m_pUI->tetrisStatusLabel->setText(
                    QString("Lines: %1").arg(m_pModel->numLines()));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *pKeyEvent)
{
    //std::cout << "keyPressEvent" << std::endl;
    //std::cout << "key = " << pKeyEvent->key() << std::endl;
    if (pKeyEvent->key() == Qt::Key_Down)
    {
        m_pModel->moveCurrentPieceDown();
    }
    else if (pKeyEvent->key() == Qt::Key_Up)
    {
        m_pModel->rotateCurrentPiece();
    }
    else if (pKeyEvent->key() == Qt::Key_Space)
    {
        m_pModel->dropCurrentPiece();
    }
    else if (pKeyEvent->key() == Qt::Key_Left)
    {
        m_pModel->moveCurrentPieceLeft();
    }
    else if (pKeyEvent->key() == Qt::Key_Right)
    {
        m_pModel->moveCurrentPieceRight();
    }
    else if (pKeyEvent->key() == Qt::Key_P)
    {
        m_pModel->togglePause();
    }
    else if (pKeyEvent->key() == Qt::Key_R)
    {
        m_pModel->reset();
    }
}

MainWindow::~MainWindow()
{
    delete m_pUI;
    delete m_pModel;
    delete m_pTimer;
}
