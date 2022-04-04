#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>
#include <QTimer>
//#include "hellotriangle.hpp"
#include "matrixtransform.hpp"
//#include "illumination.hpp"

class MainWindow : public QWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWindow *parent = 0);
    ~MainWindow();

private slots:
    void onTimeout();

private:
    bool event(QEvent *event) override;

private:
    IGlesHandle *m_pIGlesHandle;
    QTimer m_timer;
};

#endif // MAINWINDOW_H
