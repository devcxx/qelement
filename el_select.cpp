#include "el_select.h"
#include <QStylePainter>
#include <QStyledItemDelegate>

EL_BEGIN_NAMESPACE

Select::Select(QWidget* parent)
    : QComboBox(parent)
{
    setItemDelegate(new QStyledItemDelegate());
    QString styleSheet;
    styleSheet += "QComboBox { border: 1px solid #dcdfe6; border-radius: 4px; background-color: white;}";
    styleSheet += "QComboBox:on { border: 1px solid #409eff;}";
    styleSheet += "QComboBox { color: #606266; font-family: Microsoft YaHei; font-size: 14px; padding-left: 15px;}";
    styleSheet += "QComboBox QAbstractItemView { border: 1px solid #dcdfe6; border-radius: 4px; background-color: white; outline: 0px;}";
    styleSheet += "QComboBox QAbstractItemView::item { color: #606266; font-family: Microsoft YaHei; font-size: 14px; height: 34px;}";
    styleSheet += "QComboBox QAbstractItemView::item:hover { color: #606266; background-color: #f5f7fa; padding-left: 15px;}";
    styleSheet += "QComboBox QAbstractItemView::item:selected {color: #409eff;}";
    styleSheet += "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: center right; width: 14px; height: 14px; border: none; image: url(:/images/arrow-down.png); padding-right: 8px;}";
    styleSheet += "QComboBox::drop-down:on { image: url(:/images/arrow-up.png);}";
    setStyleSheet(styleSheet);
}

QSize Select::sizeHint() const
{
    return QSize(200, 40);
}

void Select::showPopup()
{
    QComboBox::showPopup();
    QWidget* popup = this->findChild<QFrame*>();
    if (popup != NULL) {
        popup->move(popup->pos().x(), popup->pos().y() + 4);
    }
}
EL_END_NAMESPACE
