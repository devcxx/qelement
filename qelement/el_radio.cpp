#include "el_radio.h"
#include "el_awesome.h"
#include <QPainter>

EL_BEGIN_NAMESPACE

Radio::Radio(const QString& text, LabelPosition placement, QWidget* parent)
    : QAbstractButton(parent)
    , _placement(placement)
{
    setText(text);
    setCursor(Qt::PointingHandCursor);
    setCheckable(true);
}

QSize Radio::sizeHint() const
{
    if (text().isEmpty()) {
        return QSize(40, 40);
    }
    QFont font("Microsoft YaHei");
    font.setPixelSize(14);
    QFontMetrics metrics(font);
    return QSize(metrics.boundingRect(text()).size().width() + 30, 40);
}

QColor Radio::getColor()
{
    if (isEnabled()) {
        if (isChecked()) {
            return QColor(0x409eff);
        } else {
            return QColor(0x606266);
        }
    } else {
        return QColor(0xc0c4cc);
    }
}

QIcon Radio::getIcon()
{
    if (isEnabled()) {
        if (isChecked()) {
            return qAwesome->icon(fa::fa_solid, fa::fa_circle_dot,
                { { "color", QColor(0x409eff) } });
        } else {
            return qAwesome->icon(fa::fa_regular, fa::fa_o,
                { { "color", QColor(0x606266) } });
        }
    } else {
        if (isChecked()) {
            return qAwesome->icon(fa::fa_solid, fa::fa_circle_dot,
                { { "color", QColor(0xc0c4cc) } });
        } else {
            return qAwesome->icon(fa::fa_regular, fa::fa_o,
                { { "color", QColor(0xc0c4cc) } });
        }
    }
}

void Radio::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    QPen pen;
    pen.setColor(getColor());
    QFont f("Microsoft YaHei");
    const int fontSize = 14;
    f.setPixelSize(fontSize);
    QFontMetrics metrics(f);
    int textWidth = metrics.boundingRect(text()).size().width();
    painter.setFont(f);
    painter.setPen(pen);
    const int iconSize = 16;
    const int margin = 4;
    if (LabelPosition::LP_Left == _placement) {
        painter.drawText(margin, 0, textWidth, height(), Qt::AlignCenter, text());
    } else {
        painter.drawText(iconSize + margin * 2, 0, textWidth, height(), Qt::AlignCenter, text());
    }
    QPixmap pixmap = getIcon().pixmap(iconSize, iconSize);
    int posY = (height() - iconSize) / 2 + 1;
    if (LabelPosition::LP_Left == _placement) {
        painter.drawPixmap(textWidth + margin * 2, posY, iconSize, iconSize, pixmap);
    } else {
        painter.drawPixmap(margin, posY, iconSize, iconSize, pixmap);
    }
}

EL_END_NAMESPACE
