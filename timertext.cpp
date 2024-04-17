#include "timertext.h"

#include <QMouseEvent>

#include <format>

TimerText::TimerText() : timer_(new QBasicTimer()), elapse_(new QElapsedTimer()), elapsed_(std::chrono::nanoseconds::zero()) {
    setText("00:00:00");
}

void TimerText::start() {
    timer_->start(1000, this);
    elapse_->start();
}

void TimerText::pause()
{
    timer_->stop();
    elapsed_ += elapse_->durationElapsed();
}

void TimerText::stop() {
    timer_->stop();
    elapsed_ = std::chrono::nanoseconds::zero();
    setText("00:00:00");
    repaint();
}

void TimerText::timerEvent(QTimerEvent *) {
    std::chrono::nanoseconds elapsed = elapsed_ + elapse_->durationElapsed();
    setText(QString::fromStdWString(std::format(L"{:%H:%M:%S}", std::chrono::duration_cast<std::chrono::seconds>(elapsed))));
    repaint();
}

void TimerText::mousePressEvent(QMouseEvent *ev)
{
    pressedButtons_ |= ev->button();
}

void TimerText::mouseMoveEvent(QMouseEvent *ev)
{
    movedButtons_ |= ev->buttons();
}

void TimerText::mouseReleaseEvent(QMouseEvent *ev)
{
    // Is a click if there is a press and hasn't moved
    bool isClick = pressedButtons_ & ev->button() && !(movedButtons_ & ev->button());

    // Clean up
    movedButtons_ &= ~ev->button();
    pressedButtons_ &= ~ev->button();

    if (!isClick)
        return;

    if (ev->button() == Qt::MouseButton::LeftButton) {
        if (timer_->isActive())
            pause();
        else
            start();
    }
    else if(ev->button() == Qt::MouseButton::MiddleButton) {
        stop();
    }
}
