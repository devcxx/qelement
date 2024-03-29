#include "el_link.h"
#include "el_style.h"
#include <QColor>

EL_BEGIN_NAMESPACE

Link::Link(const QString& text, const QString link, Type type, QWidget* parent)
    : QLabel(text, parent)
    , _link(link)
{
    QWidget::setAttribute(Qt::WA_TranslucentBackground);
    QString styleSheet;
    styleSheet += QString("QLabel { color : %1;font-family: Microsoft YaHei;font-size: 14px;}").arg(getColor(type));
    styleSheet += QString("QLabel::disabled { color : %1;}").arg(getDisabledColor(type));
    setStyleSheet(styleSheet);
    setMouseTracking(true);
}

void Link::setLink(const QString& url)
{
    _link = url;
}

QString Link::getLink()
{
    return _link;
}

void Link::mousePressEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    emit linkClicked(_link);
}

QSize Link::sizeHint() const
{
    QFont font("Microsoft YaHei");
    font.setPixelSize(14);
    QFontMetrics metrics(font);
    return QSize(metrics.boundingRect(text()).size().width() + 30, 40);
}

void Link::enterEvent(QEvent* event)
{
    setCursor(Qt::PointingHandCursor);
    QLabel::enterEvent(event);
}

void Link::leaveEvent(QEvent* event)
{
    setCursor(Qt::ArrowCursor);
    QLabel::leaveEvent(event);
}

QString Link::getColor(Type type)
{
    switch (type) {
    case Default:
        return Color::DefaultText;
    case Primary:
        return Color::PrimaryText;
    case Success:
        return Color::Success;
    case Warning:
        return Color::Warning;
    case Danger:
        return Color::Danger;
    case Info:
        return Color::Info;
    default:
        return Color::DefaultText;
    }
}

QString Link::getDisabledColor(Type type)
{
    switch (type) {
    case Default:
        return Color::DefaultTextDisabled;
    case Primary:
        return Color::PrimaryTextDisabled;
    case Success:
        return Color::SuccessDisabled;
    case Warning:
        return Color::WarningDisabled;
    case Danger:
        return Color::DangerDisabled;
    case Info:
        return Color::InfoDisabled;
    default:
        return Color::DefaultTextDisabled;
    }
}

EL_END_NAMESPACE
