#ifndef EL_RADIO_H
#define EL_RADIO_H

#include "el_global.h"
#include <QAbstractButton>

EL_BEGIN_NAMESPACE

// Radio 单选框
class EL_EXPORT Radio : public QAbstractButton {
    Q_OBJECT
public:
    // 文本位置
    enum LabelPosition {
        LP_Left, // 文字在左
        LP_Right, // 文字在右
    };

    Radio(const QString& text, LabelPosition placement = LP_Right, QWidget* parent = nullptr);

protected:
    QSize sizeHint() const;
    void paintEvent(QPaintEvent* event);
    QColor getColor();
    QIcon getIcon();

private:
    LabelPosition _placement;
};

EL_END_NAMESPACE

#endif // EL_RADIO_H
