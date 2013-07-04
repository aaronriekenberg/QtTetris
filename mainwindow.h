#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include <boost/functional/hash.hpp>
#include <unordered_map>
#include <unordered_set>
#include "tetrismodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    virtual ~MainWindow();

public slots:
    void modelUpdated(
            TetrisModel::UpdatedStatus_t stackCellsUpdated,
            TetrisModel::UpdatedStatus_t currentPieceUpdated);

protected:
    virtual void keyPressEvent(QKeyEvent *pKeyEvent) override;
    
private:
    Ui::MainWindow* m_pUI = nullptr;

    TetrisModel* m_pModel = nullptr;

    QTimer* m_pTimer = nullptr;

    std::unordered_map<TetrisCoordinate, QWidget*,
        boost::hash<TetrisCoordinate>> m_allWidgets;

    std::unordered_set<TetrisCoordinate,
        boost::hash<TetrisCoordinate>> m_currentPieceCoordinates;

    std::unordered_set<TetrisCoordinate,
        boost::hash<TetrisCoordinate>> m_stackCellCoordinates;
};

#endif // MAINWINDOW_H
