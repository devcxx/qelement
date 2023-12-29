#include "el_messagebox.h"
#include "el_awesome.h"
#include "el_button.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>
#include <QtGui/qtextdocument.h>

EL_BEGIN_NAMESPACE

MessageBox::MessageBox(const QIcon& icon, const QString& title, const QString& text, QWidget* parent)
    : FramelessWindow<QDialog>(true, parent, true)
{
    init(icon, title, text);
}

int MessageBox::alert(QWidget* parent, const QString& title, const QString& text, const QString& confirmButtonText)
{
    return showNewMessageBox(parent, {}, title, text, StandardButton::Ok, StandardButton::Ok, { { StandardButton::Ok, confirmButtonText } });
}

int MessageBox::confirm(QWidget* parent, const QString& title, const QString& text, const QString& confirmButtonText, const QString& cancelButtonText)
{
    QVariantMap options;
    options.insert("color", QColor(0xe6a23c));
    options.insert("color-active", QColor(0xe6a23c));
    QIcon icon = qAwesome->icon(fa::fa_solid, fa::fa_circle_question, options);
    return showNewMessageBox(parent, icon, title, text, StandardButton::Cancel | StandardButton::Ok,
        StandardButton::Cancel,
        { { StandardButton::Cancel, cancelButtonText }, { StandardButton::Ok, confirmButtonText } });
}

MessageBox::StandardButton MessageBox::showNewMessageBox(QWidget* parent, const QIcon& icon, const QString& title, const QString& text,
    StandardButtons buttons, StandardButton defaultButton, ButtonText buttonText)
{
    MessageBox msgBox(icon, title, text, parent);

    uint mask = MessageBox::LastButton;
    while (mask >= MessageBox::FirstButton) {
        uint sb = buttons & mask;
        mask >>= 1;
        if (!sb)
            continue;
        QPushButton* button = msgBox.addButton((StandardButton)sb, buttonText[(StandardButton)sb]);
        if (sb == defaultButton) {
            msgBox.setDefaultButton(button);
        }
    }

    return (StandardButton)msgBox.exec();
}

void MessageBox::setDefaultButton(QPushButton* button)
{
    if (button == nullptr)
        return;

    button->setDefault(true);
    button->setFocus();
}

QPushButton* MessageBox::addButton(MessageBox::StandardButton button, const QString& buttonText)
{
    QPushButton* pushButton = nullptr;
    pushButton = new Button(buttonText, Button::BT_Primary, Button::BS_Default, this);
    connect(pushButton, &QPushButton::clicked, [this, button] {
        done(button);
    });
    _buttonBox->addWidget(pushButton);
    return pushButton;
}

void MessageBox::init(const QIcon& icon, const QString& title, const QString& text)
{
    setStyleSheet("border-radius: 4px;");
    _label = new QLabel;
    _label->setTextInteractionFlags(Qt::TextInteractionFlags(style()->styleHint(QStyle::SH_MessageBox_TextInteractionFlags, nullptr, this)));
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    _label->setOpenExternalLinks(true);
    _iconLabel = new QLabel(this);
    _iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (!icon.isNull())
        _iconLabel->setPixmap(icon.pixmap(QSize(24, 24)));

    _titleLabel = new QLabel;
    _titleLabel->setStyleSheet("QLabel { font-family: Microsoft YaHei; font-size: 18px; color: #303133}");
    _titleLabel->setText(title);

    _label->setStyleSheet("QLabel { font-family: Microsoft YaHei; font-size: 14px; color: #606266}");

    setupLayout();

    if (!title.isEmpty() || !text.isEmpty()) {
        setWindowTitle(title);
        setText(text);
    }

    setContentsMargins(12, 12, 12, 12);
    setMinimumSize(400, 200);

    setModal(true);
}

QPushButton* MessageBox::closeButton()
{
    QPushButton* closeBtn = new QPushButton();
    QVariantMap options;
    options.insert("color", QColor(0x909399));
    options.insert("color-active", QColor(0x409eff));
    QIcon icon = qAwesome->icon(fa::fa_solid, fa::fa_close, options);
    closeBtn->setIcon(icon);
    closeBtn->setStyleSheet("QPushButton { background-color: transparent; border: 0px }");
    connect(closeBtn, &QPushButton::clicked, [this] {
        done(MessageBox::Close);
    });
    return closeBtn;
}

void MessageBox::setupLayout()
{
    QWidget* centralWidget = new QWidget();
    QHBoxLayout* bkLayout = new QHBoxLayout();
    bkLayout->setContentsMargins(0, 0, 0, 0);
    bkLayout->addWidget(centralWidget);
    setLayout(bkLayout);

    // 窗口拖动部位
    setTitlebar({ centralWidget, _label });

    // 创建窗口阴影效果
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    shadow->setColor(QColor(0, 0, 0, 60));
    shadow->setOffset(2, 2);
    shadow->setBlurRadius(12);
    centralWidget->setGraphicsEffect(shadow);

    const QPixmap* piamap = _iconLabel->pixmap();
    const bool hasIcon = piamap != nullptr && !piamap->isNull();

    QVBoxLayout* mainLayout = new QVBoxLayout();

    QHBoxLayout* titleLeft = new QHBoxLayout();
    titleLeft->setAlignment(Qt::AlignLeft);
    if (_titleIcon) {
        titleLeft->addWidget(_titleIcon);
    }
    titleLeft->addWidget(_titleLabel);

    // 标题栏部分
    QHBoxLayout* titleRight = new QHBoxLayout();
    titleRight->setAlignment(Qt::AlignRight);
    QPushButton* closeBtn = closeButton();
    titleRight->addWidget(closeBtn);

    QHBoxLayout* titleBar = new QHBoxLayout();
    titleBar->addLayout(titleLeft);
    titleBar->addLayout(titleRight);

    mainLayout->addLayout(titleBar);

    QHBoxLayout* contentLayout = new QHBoxLayout;
    contentLayout->setContentsMargins(10, 0, 10, 0);
    if (hasIcon)
        contentLayout->addWidget(_iconLabel, Qt::AlignCenter);
    _iconLabel->setVisible(hasIcon);

    contentLayout->addWidget(_label, Qt::AlignCenter);

    _buttonBox = new QHBoxLayout();
    _buttonBox->addStretch(0);

    mainLayout->addLayout(contentLayout);
    mainLayout->addLayout(_buttonBox);

    centralWidget->setLayout(mainLayout);
}

void MessageBox::setText(const QString& text)
{
    _label->setText(text);
    _label->setWordWrap(_label->textFormat() == Qt::RichText
        || (_label->textFormat() == Qt::AutoText && Qt::mightBeRichText(text)));
}

EL_END_NAMESPACE
