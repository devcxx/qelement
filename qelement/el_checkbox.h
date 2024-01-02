#ifndef EL_CHECKBOX_H
#define EL_CHECKBOX_H

#include "el_global.h"
#include <QAbstractButton>

EL_BEGIN_NAMESPACE

// Checkbox 多选框
class EL_EXPORT Checkbox : public QAbstractButton {
    Q_OBJECT
public:
    // 文本位置
    enum LabelPosition {
        LP_Left, // 文字在左
        LP_Right, // 文字在右
    };
    Checkbox(const QString& text, LabelPosition placement = LP_Right, QWidget* parent = nullptr);

protected:
    QSize sizeHint() const;
    void paintEvent(QPaintEvent* event);
    QColor getColor();
    QIcon getIcon();

private:
    LabelPosition _placement;
};

EL_END_NAMESPACE

#endif // EL_CHECKBOX_H
