#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    bool eventFilter(QObject *obj, QEvent *ev) override;
private:
    Ui::MainWindow *ui;
    QPoint moveBase_;
    QPointF moveStart_;
};

#endif // MAINWINDOW_H
