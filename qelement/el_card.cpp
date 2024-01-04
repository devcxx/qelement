#include "el_card.h"
#include <QPainter>
#include <QStyleOptionButton>

EL_BEGIN_NAMESPACE

Card::Card(const QIcon& icon, const QString& title, const QString& content, QWidget* parent)
    : QAbstractButton(parent)
    , _content(content)
{
    setIcon(icon);
    setText(title);
}

QSize Card::sizeHint() const
{
    return QSize(230, 70);
}

void Card::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    const int leftOffsetX = 15;
    const int topOffsetY = 15;

    QString title = text();

    QFont titleFont("Microsoft YaHei");
    titleFont.setPixelSize(14);
    QFontMetrics fmTitle(titleFont);
    QRect fmRectTitle = fmTitle.boundingRect(title);

    int iconSize = 40;

    double titlePosX = iconSize + leftOffsetX * 2;
    double titlePosY = (height() - iconSize) / 2;
    double titleWidth = fmRectTitle.width();
    double titleHeight = fmRectTitle.height();

    QFont contentFont("Microsoft YaHei");
    contentFont.setPixelSize(12);
    QFontMetrics fmContent(contentFont);
    QRect fmRectContext = fmContent.boundingRect(_content);

    double contentPosX = titlePosX;
    double contentPosY = height() / 2 + iconSize / 2 - fmRectContext.height();
    double contentWidth = fmRectContext.width();
    double contentHeight = fmRectContext.height();

    QColor titleColor(0x606266);
    QColor contentColor(0x909399);

    if (!isEnabled()) {
        titleColor = QColor(0xc0c4cc);
        contentColor = QColor(0xc0c4cc);
    }

    QPainter painter(this);

    QStyleOptionButton option;
    option.initFrom(this);
    if (option.state & QStyle::State_MouseOver) {
        painter.fillRect(option.rect, QBrush(QColor(0xf6f9fc)));
    }

    QRectF titleRect(titlePosX, titlePosY, titleWidth, titleHeight);
    painter.setPen(titleColor);
    painter.setFont(titleFont);
    painter.drawText(titleRect, Qt::AlignLeft | Qt::AlignTop, title);

    QRectF contentRect(contentPosX, contentPosY, contentWidth, contentHeight);
    painter.setPen(contentColor);
    painter.setFont(contentFont);
    painter.drawText(contentRect, Qt::AlignLeft | Qt::AlignBottom, _content);

    QPixmap pixmap = icon().pixmap(iconSize, iconSize);
    if (!isEnabled()) {
        iconToGrayscale(&pixmap);
    }
    painter.drawPixmap(QRect(leftOffsetX, topOffsetY, iconSize, iconSize), pixmap);
}

void Card::iconToGrayscale(QPixmap* pm)
{
    QImage qi(pm->toImage());
    int h = qi.height();
    int w = qi.width();
    QRgb c_rgb;
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            c_rgb = qi.pixel(i, j);
            int k = qMin(qRound(0.3 * qRed(c_rgb) + 0.59 * qGreen(c_rgb) + 0.11 * qBlue(c_rgb)), 255);
            qi.setPixel(i, j, qRgba(k, k, k, qAlpha(c_rgb)));
        }
    }
    *pm = QPixmap::fromImage(qi);
}

EL_END_NAMESPACE
