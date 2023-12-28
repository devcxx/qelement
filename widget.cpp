#include "widget.h"
#include "QtAwesome.h"
#include "el_avatar.h"
#include "el_button.h"
#include "el_input.h"
#include "el_link.h"
#include "el_switch.h"
#include "ui_widget.h"

#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

#include <QDebug>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setStyleSheet("background-color: white");

    QVBoxLayout* vLayout = new QVBoxLayout();

    QHBoxLayout* hLayout = new QHBoxLayout();
    vLayout->addLayout(hLayout);

    // Link 文字链接
    el::Link* link = new el::Link(el::Link::Danger, this);
    link->setText("默认链接");
    link->setLink("https://www.baidu.com");
    // link->setDisabled(true);
    connect(link, &el::Link::linkClicked, [](const QString& link) {
        qDebug() << "linkClicked" << link;
    });
    el::Link* link2 = new el::Link(el::Link::Success, this);
    link2->setText("默认链接");
    link2->setLink("https://www.baidu.com");
    link2->setDisabled(true);

    hLayout->addWidget(link);
    hLayout->addWidget(link2);

    // Input 输入框
    QHBoxLayout* hLayout2 = new QHBoxLayout();
    vLayout->addLayout(hLayout2);
    el::Input* input = new el::Input(el::Input::Clearable, this);
    el::Input* input2 = new el::Input(el::Input::ShowPassword, this);
    el::Input* input3 = new el::Input(el::Input::Calendar, this);
    hLayout2->addWidget(input);
    hLayout2->addWidget(input2);
    hLayout2->addWidget(input3);

    // Button 按钮
    QHBoxLayout* hLayout3 = new QHBoxLayout();
    vLayout->addLayout(hLayout3);
    el::Button* btn = new el::Button("默认按钮");
    el::Button* btn2 = new el::Button("主要按钮", el::Button::BT_Primary);
    el::Button* btn3 = new el::Button("成功按钮", el::Button::BT_Success);
    el::Button* btn4 = new el::Button("警告按钮", el::Button::BT_Warning);
    el::Button* btn5 = new el::Button("危险按钮", el::Button::BT_Danger);
    el::Button* btn6 = new el::Button("信息按钮", el::Button::BT_Info);

    hLayout3->addWidget(btn);
    hLayout3->addWidget(btn2);
    hLayout3->addWidget(btn3);
    hLayout3->addWidget(btn4);
    hLayout3->addWidget(btn5);
    hLayout3->addWidget(btn6);

    // 圆角 按钮
    QHBoxLayout* hLayout4 = new QHBoxLayout();
    vLayout->addLayout(hLayout4);
    el::Button* rbtn2 = new el::Button("主要按钮", el::Button::BT_Primary, el::Button::BS_Round);
    el::Button* rbtn3 = new el::Button("成功按钮", el::Button::BT_Success, el::Button::BS_Round);
    el::Button* rbtn4 = new el::Button("警告按钮", el::Button::BT_Warning, el::Button::BS_Round);
    el::Button* rbtn5 = new el::Button("危险按钮", el::Button::BT_Danger, el::Button::BS_Round);
    el::Button* rbtn6 = new el::Button("信息按钮", el::Button::BT_Info, el::Button::BS_Round);

    hLayout4->addWidget(rbtn2);
    hLayout4->addWidget(rbtn3);
    hLayout4->addWidget(rbtn4);
    hLayout4->addWidget(rbtn5);
    hLayout4->addWidget(rbtn6);

    // ICON 按钮
    QHBoxLayout* hLayout5 = new QHBoxLayout();
    vLayout->addLayout(hLayout5);
    el::Button* ibtn = new el::Button(fa::fa_add, el::Button::BT_Default);
    el::Button* ibtn2 = new el::Button(fa::fa_add, el::Button::BT_Primary);
    el::Button* ibtn3 = new el::Button(fa::fa_bookmark, el::Button::BT_Success);
    el::Button* ibtn4 = new el::Button(fa::fa_camera, el::Button::BT_Warning);
    el::Button* ibtn5 = new el::Button(fa::fa_dashboard, el::Button::BT_Danger);
    el::Button* ibtn6 = new el::Button(fa::fa_edit, el::Button::BT_Info);
    el::Button* ibtn7 = new el::Button("搜索", fa::fa_search, el::Button::BT_Primary);

    hLayout5->addWidget(ibtn);
    hLayout5->addWidget(ibtn2);
    hLayout5->addWidget(ibtn3);
    hLayout5->addWidget(ibtn4);
    hLayout5->addWidget(ibtn5);
    hLayout5->addWidget(ibtn6);
    hLayout5->addWidget(ibtn7);

    // Switch 开关
    QHBoxLayout* hLayout6 = new QHBoxLayout();
    vLayout->addLayout(hLayout6);
    el::Switch* switch1 = new el::Switch("开关");
    el::Switch* switch2 = new el::Switch("禁用开关");
    switch2->setDisabled(true);
    hLayout6->addWidget(switch1);
    hLayout6->addWidget(switch2);

    // Avatar 头像
    QHBoxLayout* hLayout7 = new QHBoxLayout();
    vLayout->addLayout(hLayout7);
    el::Avatar* avatar1 = new el::Avatar("姓");
    el::Avatar* avatar2 = new el::Avatar(QImage(":/avatar.png"));
    hLayout7->addWidget(avatar1);
    hLayout7->addWidget(avatar2);

    setLayout(vLayout);
}

Widget::~Widget()
{
    delete ui;
}
