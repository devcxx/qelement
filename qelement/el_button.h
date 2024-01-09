#ifndef EL_BUTTON_H
#define EL_BUTTON_H

#include "el_global.h"
#include <QPushButton>

EL_BEGIN_NAMESPACE

// Button 按钮
class EL_EXPORT Button : public QPushButton {
    Q_OBJECT
public:
    enum ButtonType {
        BT_Default, // 默认按钮
        BT_Primary, // 主要按钮
        BT_Success, // 成功按钮
        BT_Warning, // 警告按钮
        BT_Danger, // 危险按钮
        BT_Info // 信息按钮
    };
    Q_ENUM(ButtonType)

    enum ButtonStyle {
        BS_Default, // 默认
        BS_Round, // 圆角
        BS_Circle // 圆形
    };
    Q_ENUM(ButtonStyle)

    explicit Button(QWidget *parent = nullptr);
    // 默认按钮
    Button(const QString& text, ButtonType type = BT_Default, ButtonStyle style = BS_Default, QWidget* parent = nullptr);
    // 图标按钮
    Button(const QIcon& icon, ButtonType type = BT_Default, ButtonStyle style = BS_Default, QWidget* parent = nullptr);
    // 文字图标按钮
    Button(const QString& text, const QIcon& icon, ButtonType type = BT_Default, ButtonStyle style = BS_Default, QWidget* parent = nullptr);
    // FontAwesome图标按钮
    Button(int character, ButtonType type = BT_Default, ButtonStyle style = BS_Circle, QWidget* parent = nullptr);
    // FontAwesome文字图标按钮
    Button(const QString& text, int character, ButtonType type = BT_Default, ButtonStyle style = BS_Default, QWidget* parent = nullptr);

    void init(ButtonType type = BT_Default, ButtonStyle style = BS_Default);
    void init(const QIcon& icon, ButtonType type = BT_Default, ButtonStyle style = BS_Default);
    void init(int character, ButtonType type = BT_Default, ButtonStyle style = BS_Circle);
protected:
    QSize sizeHint() const;

    QString getBorderStyle(ButtonType type, ButtonStyle style);
    QString getColorStyle(ButtonType type);
    QString getBkColorStyle(ButtonType type);
};

EL_END_NAMESPACE

#endif // EL_BUTTON_H
