#include "el_button.h"
#include "el_awesome.h"

EL_BEGIN_NAMESPACE

Button::Button(const QString& text, ButtonType type, ButtonStyle style, QWidget* parent)
    : Button(text, QIcon(), type, style, parent)
{
}

Button::Button(const QIcon& icon, ButtonType type, ButtonStyle style, QWidget* parent)
    : Button(QString(), icon, type, style, parent)
{
}

Button::Button(const QString& text, const QIcon& icon, ButtonType type, ButtonStyle style, QWidget* parent)
    : QPushButton(icon, text, parent)
{
    QString styleSheet;
    styleSheet += "QPushButton {font-family: Microsoft YaHei; font-size: 14px;}";
    styleSheet += getBorderStyle(type, style);
    styleSheet += getColorStyle(type);
    styleSheet += getBkColorStyle(type);
    setStyleSheet(styleSheet);
    autoResize(text, icon.isNull());
}

Button::Button(int character, ButtonType type, ButtonStyle style, QWidget* parent)
    : Button(QString(), character, type, style, parent)
{
}

Button::Button(const QString& text, int character, ButtonType type, ButtonStyle style, QWidget* parent)
    : QPushButton(text, parent)
{
    QVariantMap options;
    if (type == BT_Default) {
        options.insert("color", QColor(0x606266));
        options.insert("color-active", QColor(0x409eff));
    } else {
        options.insert("color", QColor(0xffffff));
        options.insert("color-active", QColor(0xffffff));
    }

    QIcon icon = qAwesome->icon(fa::fa_solid, character, options);
    setIcon(icon);
    QString styleSheet;
    styleSheet += "QPushButton {font-family: Microsoft YaHei; font-size: 14px;}";
    styleSheet += getBorderStyle(type, style);
    styleSheet += getColorStyle(type);
    styleSheet += getBkColorStyle(type);
    setStyleSheet(styleSheet);

    if (style == BS_Circle) {
        setFixedSize(40, 40);
    } else {
        autoResize(text, true);
    }
}

void Button::autoResize(const QString& text, bool hasIcon)
{
    QFont font("Microsoft YaHei");
    font.setPixelSize(14);
    QFontMetrics metrics(font);
    QSize size = metrics.boundingRect(text).size();
    int newWidth = size.width() + 30;
    if (hasIcon) {
        newWidth += iconSize().width();
    }
    setFixedSize(newWidth, 40);
}

QString Button::getBorderStyle(ButtonType type, ButtonStyle style)
{
    QString borderStyle;
    // 圆角样式
    if (style == BS_Default) {
        borderStyle += "QPushButton { border-radius: 4px; }";
    } else if (style == BS_Round) {
        borderStyle += "QPushButton { border-radius: 20px; }";
    } else if (style == BS_Circle) {
        borderStyle += "QPushButton { border-radius: 20px; }";
    }
    // 边框样式
    if (type == BT_Default) {
        borderStyle += "QPushButton { border: 1px solid #dcdfe6; }";
        borderStyle += "QPushButton:pressed { border: 1px solid #c6e2ff; }";
    } else {
        borderStyle += "QPushButton { border: none; }";
    }

    return borderStyle;
}

QString Button::getColorStyle(ButtonType type)
{
    QString colorStyle;
    if (type == BT_Default) {
        colorStyle += "QPushButton { color: #606266; }";
        colorStyle += "QPushButton:hover { color: #409eff; }";
        colorStyle += "QPushButton:pressed { color: #409eff; }";
    } else {
        colorStyle += "QPushButton { color: #ffffff; }";
    }
    return colorStyle;
}

QString Button::getBkColorStyle(ButtonType type)
{
    QString bkColorStyle;
    if (type == BT_Default) {
        bkColorStyle += "QPushButton { background: #ffffff; }";
        bkColorStyle += "QPushButton:hover { background: #ecf5ff; }";
        bkColorStyle += "QPushButton:pressed { background: #ecf5ff; }";
    } else if (type == BT_Primary) {
        bkColorStyle += "QPushButton { background: #409eff; }";
        bkColorStyle += "QPushButton:hover { background: #66b1ff; }";
        bkColorStyle += "QPushButton:pressed { background: #3a8ee6; }";
    } else if (type == BT_Success) {
        bkColorStyle += "QPushButton { background: #67c23a; }";
        bkColorStyle += "QPushButton:hover { background: #85ce61; }";
        bkColorStyle += "QPushButton:pressed { background: #5daf34; }";
    } else if (type == BT_Warning) {
        bkColorStyle += "QPushButton { background: #e6a23c; }";
        bkColorStyle += "QPushButton:hover { background: #ebb563; }";
        bkColorStyle += "QPushButton:pressed { background: #cf9236; }";
    } else if (type == BT_Danger) {
        bkColorStyle += "QPushButton { background: #f56c6c; }";
        bkColorStyle += "QPushButton:hover { background: #f78989; }";
        bkColorStyle += "QPushButton:pressed { background: #dd6161; }";
    } else if (type == BT_Info) {
        bkColorStyle += "QPushButton { background: #909399; }";
        bkColorStyle += "QPushButton:hover { background: #a6a9ad; }";
        bkColorStyle += "QPushButton:pressed { background: #82848a; }";
    }
    return bkColorStyle;
}

EL_END_NAMESPACE
