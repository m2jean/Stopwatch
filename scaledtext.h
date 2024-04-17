#ifndef SCALEDTEXT_H
#define SCALEDTEXT_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class ScaledText;
}

class ScaledText : public QWidget
{
    Q_OBJECT

public:
    explicit ScaledText(QWidget *parent = nullptr);
    ~ScaledText();

    const QString& getText() const { return text_; }
    void setText(const QString &text) { text_ = text; }
protected:
    void paintEvent(QPaintEvent *) override;
private:
    QString text_;
    QFont font_;
};

#endif // SCALEDTEXT_H
