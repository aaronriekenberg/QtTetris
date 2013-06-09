#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tetrisconstants.h"
#include "tetrismodel.h"
#include <QKeyEvent>
#include <iostream>

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
            QFrame* pFrame = new QFrame();
            palette = pFrame->palette();
            palette.setColor(pFrame->backgroundRole(), Qt::black);
            pFrame->setPalette(palette);
            pFrame->setAutoFillBackground(true);
            m_pUI->tetrisGrid->addWidget(pFrame, row, column);
            TetrisCoordinate coordinate(row, column);
            m_tetrisCoordinateToQFrame[coordinate] = pFrame;
        }
    }


    QObject::connect(m_pTimer, SIGNAL(timeout()), m_pModel, SLOT(periodicUpdate()));
    m_pTimer->start(250);

    QObject::connect(m_pModel, SIGNAL(modelUpdated()), this, SLOT(modelUpdated()));
    modelUpdated();
}

void MainWindow::modelUpdated()
{
    const std::map<TetrisCoordinate, TetrisConstants::TetrisCellColor>& drawableCells =
            m_pModel->drawableCells();
    //std::cout << "MainWindow::modelUpdated drawableCells.size = " << drawableCells.size() << std::endl;
    std::map<TetrisCoordinate, TetrisConstants::TetrisCellColor>::const_iterator drawableCellsIter;
    for (int row = 0; row < TetrisConstants::NUM_ROWS; ++row)
    {
        for (int column = 0; column < TetrisConstants::NUM_COLUMNS; ++column)
        {
            TetrisCoordinate coordinate(row, column);
            QColor newQtColor(Qt::black);
            drawableCellsIter = drawableCells.find(coordinate);
            if (drawableCellsIter != drawableCells.end())
            {
                TetrisConstants::TetrisCellColor newCellColor = drawableCellsIter->second;
                switch (newCellColor)
                {
                case TetrisConstants::CELL_NOT_PRESENT:
                    newQtColor = QColor(Qt::black);
                    break;
                case TetrisConstants::CELL_RED:
                    newQtColor = QColor(Qt::red);
                    break;
                case TetrisConstants::CELL_GREEN:
                    newQtColor = QColor(Qt::green);
                    break;
                case TetrisConstants::CELL_LIGHTGRAY:
                    newQtColor = QColor(Qt::lightGray);
                    break;
                case TetrisConstants::CELL_MAGENTA:
                    newQtColor = QColor(Qt::magenta);
                    break;
                case TetrisConstants::CELL_CYAN:
                    newQtColor = QColor(Qt::cyan);
                    break;
                case TetrisConstants::CELL_YELLOW:
                    newQtColor = QColor(Qt::yellow);
                    break;
                case TetrisConstants::CELL_BLUE:
                    newQtColor = QColor(Qt::blue);
                    break;
                }
            }

            QFrame* pFrame = m_tetrisCoordinateToQFrame[coordinate];
            if (newQtColor != pFrame->palette().color(pFrame->backgroundRole()))
            {
                //std::cout << "updating color for row " << row << " column " << column << std::endl;
                QPalette palette = pFrame->palette();
                palette.setColor(pFrame->backgroundRole(), newQtColor);
                pFrame->setPalette(palette);
            }
        }
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
