#include "scaledtext.h"

#include <QFontMetricsF>

ScaledText::ScaledText(QWidget *parent)
    : QWidget(parent)
{
    font_ = QFont("Calabri");
    setSizePolicy(QSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding));
}

ScaledText::~ScaledText()
{
}

void ScaledText::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    font_.setPixelSize(height());
    painter.setFont(font_);

    QFontMetrics metrics(font_);
    qreal actualWidth = metrics.size(Qt::TextSingleLine, text_).width();
    qreal xscale = width() / actualWidth;

    painter.scale(xscale, 1);
    painter.drawText(0, 0, width()/xscale, height(), Qt::AlignCenter, text_);
    painter.resetTransform();
}
