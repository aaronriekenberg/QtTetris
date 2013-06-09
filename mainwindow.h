#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QMainWindow>
#include <QTimer>
#include <map>
#include "tetrismodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void modelUpdated();

protected:
    virtual void keyPressEvent(QKeyEvent *pKeyEvent);
    
private:
    Ui::MainWindow* m_pUI;

    TetrisModel* m_pModel;

    QTimer* m_pTimer;

    std::map<TetrisCoordinate, QFrame*> m_tetrisCoordinateToQFrame;
};

#endif // MAINWINDOW_H
