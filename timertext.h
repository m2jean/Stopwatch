#ifndef TIMERTEXT_H
#define TIMERTEXT_H

#include "scaledtext.h"

#include <QBasicTimer>
#include <QElapsedTimer>

class TimerText : public ScaledText
{
    Q_OBJECT
public:
    TimerText();

    void start();
    void pause();
    void stop();
protected:
    void timerEvent(QTimerEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
private:
    QBasicTimer *timer_;
    QElapsedTimer *elapse_;
    std::chrono::nanoseconds elapsed_;
    Qt::MouseButtons pressedButtons_;
    Qt::MouseButtons movedButtons_;
};

#endif // TIMERTEXT_H
