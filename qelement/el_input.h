#ifndef EL_INPUT_H
#define EL_INPUT_H

#include "el_global.h"
#include <QAction>
#include <QLineEdit>

EL_BEGIN_NAMESPACE

// Input 输入框
class EL_EXPORT Input : public QLineEdit {
    Q_OBJECT

public:
    enum Type {
        Default,
        Clearable, // 可清空
        ShowPassword, // 密码框
        Calendar, // 日历
    };
    Q_ENUM(Type)

    Input(Type type = Default, QWidget* parent = nullptr);
};

EL_END_NAMESPACE

#endif // EL_INPUT_H
