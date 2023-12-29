#ifndef EL_LINK_H
#define EL_LINK_H

#include "el_global.h"
#include <QLabel>

EL_BEGIN_NAMESPACE

// Link 文字链接
class EL_EXPORT Link : public QLabel {

    Q_OBJECT
public:
    enum Type {
        Default, // 默认链接
        Primary, // 主要链接
        Success, // 成功链接
        Warning, // 警告链接
        Danger, // 危险链接
        Info // 信息链接
    };
    Q_ENUM(Type)

    Link(const QString& text, const QString link, Type type = Default, QWidget* parent = nullptr);
    void setLink(const QString& link);
    QString getLink();

signals:
    void linkClicked(const QString& link);

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

    QString getColor(Type type);
    QString getDisabledColor(Type type);
    void autoResize(const QString& text);

private:
    QString _link;
};

EL_END_NAMESPACE

#endif // EL_LINK_H
