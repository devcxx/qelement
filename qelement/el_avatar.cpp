#include "el_avatar.h"

#include <QFile>
#include <QPainter>
#include <QPainterPath>

EL_BEGIN_NAMESPACE

Avatar::Avatar(QWidget* parent)
    : QWidget { parent }
{
    QSizePolicy policy(QSizePolicy::MinimumExpanding,
        QSizePolicy::MinimumExpanding);
    setSizePolicy(policy);

    connect(&_provider, &ImageProvider::imageReady, this, &Avatar::onImageReady);
}

Avatar::Avatar(const QIcon& icon, QWidget* parent)
    : Avatar(parent)
{
    setIcon(icon);
}

Avatar::Avatar(const QString& letter, QWidget* parent)
    : Avatar(parent)
{
    setLetter(letter);
}

Avatar::Avatar(const QImage& image, QWidget* parent)
    : Avatar(parent)
{
    setImage(image);
}

QSize Avatar::sizeHint() const
{
    return QSize(_size + 2, _size + 2);
}

void Avatar::setSize(int size)
{
    _size = size;

    if (!_image.isNull()) {
        _pixmap = QPixmap::fromImage(_image.scaled(_size, _size,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation));
    }

    update();
}

int Avatar::size() const
{
    return _size;
}

void Avatar::setLetter(const QString& letter)
{
    _letter = letter;
    _type = Letter;
    update();
}

void Avatar::setImage(const QImage& image)
{
    _image = image;
    _type = Image;

    _pixmap = QPixmap::fromImage(image.scaled(_size, _size,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation));
    update();
}

void Avatar::setIcon(const QIcon& icon)
{
    _icon = icon;
    _type = Icon;
    update();
}

void Avatar::setUrl(const QString& url)
{
    if (url.isEmpty()) {
        return;
    }
    _provider.getNetworkImage(url);
}

void Avatar::onImageReady(QString url, QString filePath)
{
    Q_UNUSED(url)
    if (QFile::exists(filePath)) {
        setImage(QImage(filePath));
        return;
    }
}

Avatar::Type Avatar::type() const
{
    return _type;
}

void Avatar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect();
    const qreal hs = _size / 2;

    if (!isEnabled()) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(0xc0c4cc));
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width() - _size) / 2, (height() - _size) / 2,
            _size, _size));
        return;
    }

    if (Image != _type) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(QColor(0xc0c4cc));
        painter.setPen(Qt::NoPen);
        painter.setBrush(brush);
        painter.drawEllipse(QRectF((width() - _size) / 2, (height() - _size) / 2,
            _size, _size));
    }

    switch (_type) {
    case Image: {
        QPainterPath path;
        path.addEllipse(width() / 2 - hs, height() / 2 - hs, _size, _size);
        painter.setClipPath(path);

        painter.drawPixmap(QRect(width() / 2 - hs, height() / 2 - hs, _size, _size), _pixmap);
        break;
    }
    case Icon: {
        QRect iconGeometry((width() - hs) / 2, (height() - hs) / 2, hs, hs);
        QPixmap pixmap = _icon.pixmap(hs, hs);
        QPainter icon(&pixmap);
        icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
        icon.fillRect(pixmap.rect(), QColor(0xffffff));
        painter.drawPixmap(iconGeometry, pixmap);
        break;
    }
    case Letter: {
        QFont f("Microsoft YaHei");
        f.setPixelSize(18);
        painter.setFont(f);
        painter.setPen(QColor(0xffffff));
        painter.setBrush(Qt::NoBrush);
        painter.drawText(r, Qt::AlignCenter, _letter);
        break;
    }
    default:
        break;
    }
}

EL_END_NAMESPACE
