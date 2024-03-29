#include "el_input.h"
#include "el_awesome.h"
#include "el_style.h"
#include <QApplication>
#include <QStyle>

EL_BEGIN_NAMESPACE

Input::Input(Type type, QWidget* parent)
    : QLineEdit(parent)
{
    QString styleSheet;
    styleSheet += "QLineEdit { border: 1px solid #dcdfe6; border-radius: 4px; }";
    styleSheet += "QLineEdit:focus { border: 1px solid #409eff; }";
    styleSheet += "QLineEdit { font-family: Microsoft YaHei; font-size: 14px; }";
    styleSheet += "QLineEdit { padding-left: 15px; padding-right: 15px; }";
    styleSheet += "QLineEdit { color: #606266; min-height: 40px; }";

    setStyleSheet(styleSheet);
    QVariantMap options;
    options.insert("color", QColor(Color::PlaceholderText));
    options.insert("color-active", QColor(Color::SecondaryText));

    if (type == Type::Clearable) {
        QAction* clearAction = new QAction;
        clearAction->setIcon(qAwesome->icon(fa::fa_solid, fa::fa_xmark_circle, options));
        addAction(clearAction, QLineEdit::TrailingPosition);
        connect(clearAction, &QAction::triggered, this, [this] { this->clear(); });
    } else if (type == Type::ShowPassword) {
        setEchoMode(QLineEdit::Password);
        QAction* showPasswordAction = new QAction;
        showPasswordAction->setCheckable(true);
        showPasswordAction->setIcon(qAwesome->icon(fa::fa_solid, fa::fa_eye, options));
        addAction(showPasswordAction, QLineEdit::TrailingPosition);
        connect(showPasswordAction, &QAction::triggered, this, [this](bool show) { this->setEchoMode(show ? QLineEdit::Normal : QLineEdit::Password); });
    } else if (type == Type::Calendar) {
        QAction* calendarAction = new QAction;
        calendarAction->setIcon(qAwesome->icon(fa::fa_solid, fa::fa_calendar_days, options));
        calendarAction->setCheckable(true);
        addAction(calendarAction, QLineEdit::TrailingPosition);
        connect(calendarAction, &QAction::triggered, this, [this](bool show) {
            // TODO: 显示日历控件
        });
    }
}

EL_END_NAMESPACE
