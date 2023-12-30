#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "FramelessWindow.hpp"
#include "el_global.h"
#include <QDialog>

class QLabel;
class QHBoxLayout;
class QPushButton;

EL_BEGIN_NAMESPACE

// MessageBox 弹框
class EL_EXPORT MessageBox : public FramelessWindow<QDialog> {
    Q_OBJECT
public:
    enum StandardButton {
        NoButton = 1 << 0, // 无按钮
        Ok = 1 << 1, // 确定
        Yes = 1 << 2, // 是
        No = 1 << 3, // 否
        Close = 1 << 4, // 关闭
        Cancel = 1 << 5, // 取消

        FirstButton = Ok,
        LastButton = Cancel,
    };

    Q_DECLARE_FLAGS(StandardButtons, StandardButton)
    Q_FLAG(StandardButtons)

    typedef QMap<StandardButton, QString> ButtonText;

    MessageBox(const QIcon& icon, const QString& title, const QString& text, QWidget* parent = nullptr);

    // 消息提示
    static int alert(QWidget* parent, const QString& title, const QString& text, const QString& confirmButtonText);
    // 确认消息
    static int confirm(QWidget* parent, const QString& title, const QString& text,
        const QString& confirmButtonText, const QString& cancelButtonText);
    // 错误消息
    static int error(QWidget* parent, const QString& title, const QString& text, const QString& confirmButtonText);

protected:
    static StandardButton showNewMessageBox(QWidget* parent, const QIcon& icon, const QString& title, const QString& text,
        StandardButtons buttons, StandardButton defaultButton, ButtonText buttonText);
    QPushButton* addButton(StandardButton button, const QString& buttonText);
    void init(const QIcon& icon, const QString& title, const QString& text);
    void setupLayout();
    void setText(const QString& text);
    void setIcon(const QIcon& icon);
    void setDefaultButton(QPushButton* button);
    QPushButton* closeButton();

private:
    QLabel* _iconLabel = nullptr;
    QLabel* _label = nullptr;
    QLabel* _titleLabel = nullptr;
    QLabel* _titleIcon = nullptr;
    QHBoxLayout* _buttonBox = nullptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(MessageBox::StandardButtons)

EL_END_NAMESPACE

#endif // MESSAGEBOX_H
