#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QSettings>

static QSettings getQSettings() {
    return QSettings("settings.ini", QSettings::IniFormat);
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent, Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings = getQSettings();
    auto savedGeometry = settings.value("MainWindow/geometry").toByteArray();
    if (!savedGeometry.isEmpty())
        restoreGeometry(savedGeometry);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings = getQSettings();
    settings.setValue("MainWindow/geometry", saveGeometry());
    QWidget::closeEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    qDebug() << "Main window pressed";
}

bool MainWindow::eventFilter(QObject *, QEvent *ev)
{
    // It assumes there's always a press event before moving
    Q_ASSERT(!this->hasMouseTracking());

    // Check move event first because it happens more frequently
    if (ev->type() == QEvent::MouseMove) {
        QMouseEvent *mev = dynamic_cast<QMouseEvent*>(ev);
        if (mev->buttons() & Qt::MouseButton::LeftButton) {
            QPointF moveTarget = moveBase_ + (mev->globalPosition() - moveStart_);
            move(moveTarget.toPoint());
        }
    }
    else if (ev->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mev = dynamic_cast<QMouseEvent*>(ev);
        if (mev->button() == Qt::MouseButton::LeftButton) {
            moveBase_ = this->pos();
            moveStart_ = mev->globalPosition();
        }
    }
    return false;
}
