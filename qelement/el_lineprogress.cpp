#include "el_lineprogress.h"
#include <QPainter>

EL_BEGIN_NAMESPACE

LineProgress::LineProgress(QWidget* parent)
    : QProgressBar(parent)
{
    setMinimum(0);
    setMaximum(100);
    setValue(0);
}

void LineProgress::setStatus(Status status)
{
    _status = status;
}

void LineProgress::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect rect = QRect(0, 0, width(), height() / 2);
    // QRect textRect = QRect(0, height() / 2, width(), height() / 2);

    const double k = (double)(value() - minimum()) / (maximum() - minimum());
    int x = (int)(rect.width() * k);
    QRect fillRect = rect.adjusted(0, 0, x - rect.width(), 0);

    painter.fillRect(rect, QBrush(QColor(0xebeef5)));
    painter.fillRect(fillRect, QBrush(getColor()));
}

QColor LineProgress::getColor()
{
    switch (_status) {
    case Default:
        return QColor(0x409eff);
    case Success:
        return QColor(0x67c23a);
    case Warning:
        return QColor(0xe6a23c);
    case Exception:
        return QColor(0xf56c6c);
    }
}

EL_END_NAMESPACE
