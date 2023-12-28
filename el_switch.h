
#ifndef EL_SWITCH_H
#define EL_SWITCH_H

#include "el_global.h"
#include <QAbstractButton>

QT_BEGIN_NAMESPACE
class QPropertyAnimation;
QT_END_NAMESPACE

EL_BEGIN_NAMESPACE

// Switch 开关
class Switch final : public QAbstractButton {
    Q_OBJECT
    Q_PROPERTY(int thumbPosition READ thumbPosition WRITE setThumbPosition NOTIFY thumbPositionChanged FINAL)

public:
    explicit Switch(QWidget* const parent = nullptr);
    explicit Switch(const QString& text, QWidget* const parent = nullptr);
    virtual ~Switch() = default;
    // 设置背景 激活/未激活 颜色
    void setTrackColor(const QColor& trackOnColor, const QColor& trackOffColor);
    // 设置滑块 激活/未激活 颜色
    void setThumbColor(const QColor& thumbOnColor, const QColor& thumbOffColor);

    virtual QSize sizeHint() const override;

signals:
    void stateChanged(int);
    void thumbPositionChanged();

protected:
    QRect indicatorRect();
    QRect textRect();

    virtual void paintEvent(QPaintEvent* const) override;
    virtual void nextCheckState() override;
    virtual void checkStateSet() override;

    void toggle(const Qt::CheckState& state);

private:
    void setThumbPosition(const int& thumbPosition);
    int thumbPosition();

    const qreal CORNER_RADIUS, THUMB_RADIUS, SHADOW_ELEVATION;
    int height;
    QMargins indicatorMargin;

    QColor trackOnColor, trackOffColor,
        thumbOnColor, thumbOffColor,
        trackDisabledColor, thumbDisabledColor;
    qreal trackDisabledOpacity, disabledTextOpacity;

    QPropertyAnimation* const thumbPosAnimation;
    int _thumbPosition;
    QPixmap shadowPixmap;
};

EL_END_NAMESPACE

#endif // EL_SWITCH_H
