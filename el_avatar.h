#ifndef EL_AVATAR_H
#define EL_AVATAR_H

#include "el_global.h"

#include <QIcon>
#include <QObject>
#include <QWidget>

EL_BEGIN_NAMESPACE

// Avatar 头像
class EL_EXPORT Avatar : public QWidget {
    Q_OBJECT
public:
    enum Type {
        Icon, // 图标
        Image, // 图片
        Letter, // 字符
    };
    Q_ENUM(Type)

    explicit Avatar(QWidget* parent = nullptr);
    explicit Avatar(const QIcon& icon, QWidget* parent = 0);
    explicit Avatar(const QString& letter, QWidget* parent = 0);
    explicit Avatar(const QImage& image, QWidget* parent = 0);

    QSize sizeHint() const Q_DECL_OVERRIDE;

    void setSize(int size);
    int size() const;

    void setLetter(const QString& letter);
    void setImage(const QImage& image);
    void setIcon(const QIcon& icon);

    Type type() const;

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
    int _size = 40;
    Type _type = Letter;
    QString _letter;
    QImage _image;
    QIcon _icon;
    QPixmap _pixmap;
};

EL_END_NAMESPACE

#endif // EL_AVATAR_H
