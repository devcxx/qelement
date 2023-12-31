#include "el_inputnumber.h"
#include "el_awesome.h"

#include <QAction>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QStyle>

EL_BEGIN_NAMESPACE

InputNumber::InputNumber(int min, int max, QWidget* parent)
    : QLineEdit { parent }
{

    QVariantMap options;
    options.insert("color", QColor(0x606266));
    options.insert("color-active", QColor(0x7fb8fe));

    _minusBtn = new QPushButton(this);
    _minusBtn->setIcon(qAwesome->icon(fa::fa_solid, fa::fa_minus, options));
    QString minusStyle;
    minusStyle += "QPushButton { background:#f5f7fa; width: 40px; height: 38px;}";
    minusStyle += "QPushButton { border-left: none; border-top: none; border-bottom: none; border-right: 1px solid #dcdfe6;}";
    minusStyle += "QPushButton { border-top-left-radius: 4px; border-bottom-left-radius: 4px;} ";
    _minusBtn->setStyleSheet(minusStyle);
    _minusBtn->setFocusProxy(this);
    connect(_minusBtn, &QPushButton::pressed, [this, min] {
        int value = text().toInt();
        value--;
        if (value < min)
            return;
        setText(QString::number(value));
    });

    _plusBtn = new QPushButton(this);
    _plusBtn->setIcon(qAwesome->icon(fa::fa_solid, fa::fa_add, options));
    QString plusStyle;
    plusStyle += "QPushButton { background:#f5f7fa; width: 40px; height: 38px;}";
    plusStyle += "QPushButton { border-left: 1px solid #dcdfe6; border-top: none; border-bottom: none; border-right: none;}";
    plusStyle += "QPushButton { border-top-right-radius: 4px; border-bottom-right-radius: 4px;} ";
    _plusBtn->setStyleSheet(plusStyle);
    _plusBtn->setFocusProxy(this);
    connect(_plusBtn, &QPushButton::pressed, [this, max] {
        int value = text().toInt();
        value++;
        if (value > max)
            return;
        setText(QString::number(value));
    });

    QString styleSheet;
    styleSheet += "QLineEdit { border-radius: 4px; border: 1px solid #dcdfe6; padding-left: 40px; padding-right: 40px;}";
    styleSheet += "QLineEdit:focus { border: 1px solid #409eff; }";
    styleSheet += "QLineEdit { qproperty-alignment: AlignHCenter;}";
    styleSheet += "QLineEdit { font-family: Microsoft YaHei; font-size: 14px; }";
    styleSheet += "QLineEdit { color: #606266; min-height: 40px; }";

    setStyleSheet(styleSheet);
    setValidator(new QIntValidator(this));
}

void InputNumber::resizeEvent(QResizeEvent* event)
{
    if (auto resizeEvent = dynamic_cast<QResizeEvent*>(event)) {
        QSize sz = _minusBtn->sizeHint();
        int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
        _minusBtn->move(1,
            (rect().bottom() - sz.height()) / 2);

        sz = _plusBtn->sizeHint();
        _plusBtn->move(rect().right() - frameWidth - sz.width(),
            (rect().bottom() - sz.height()) / 2);
    }
}

EL_END_NAMESPACE
