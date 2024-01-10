#include "el_circleprogress.h"
#include <QPainter>

EL_BEGIN_NAMESPACE

CircleProgress::CircleProgress(QWidget* parent)
    : QWidget { parent }
{
}

void CircleProgress::setPercent(int percent)
{
    if (_percent != percent) {
        _percent = percent;
        update();
    }
}

void CircleProgress::setStatus(Status status)
{
    _status = status;
}

void CircleProgress::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    _rotateAngle = 360 * _percent / 100;

    int side = qMin(width(), height());
    QRectF outRect(0, 0, side, side);
    QRectF inRect(10, 10, side - 20, side - 20);
    QString valueStr = QString("%1%").arg(QString::number(_percent));

    //画外圆
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(QColor(0xebeef5)));
    p.drawEllipse(outRect);
    p.setBrush(QBrush(getColor()));
    p.drawPie(outRect, (90 - _rotateAngle) * 16, _rotateAngle * 16);
    //画遮罩
    p.setBrush(palette().window().color());
    p.drawEllipse(inRect);
    //画文字
    QFont f = QFont("Microsoft YaHei");
    f.setPixelSize(14);
    p.setFont(f);
    p.setPen(QColor(0x606266));
    p.drawText(inRect, Qt::AlignCenter, valueStr);
}

QSize CircleProgress::sizeHint() const
{
    return QSize(120, 120);
}

QColor CircleProgress::getColor()
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
