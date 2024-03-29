#include "widget.h"
#include "QtAwesome.h"
#include "el_avatar.h"
#include "el_button.h"
#include "el_checkbox.h"
#include "el_input.h"
#include "el_link.h"
#include "el_messagebox.h"
#include "el_select.h"
#include "el_switch.h"
#include "el_inputnumber.h"
#include "el_radio.h"
#include "el_card.h"
#include "el_slider.h"
#include "el_lineprogress.h"
#include "el_circleprogress.h"
#include "ui_widget.h"

#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QStringList>
#include <QButtonGroup>

using namespace el;

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
    Link* link = new Link("默认链接", "https://www.baidu.com", Link::Danger, this);
    // link->setDisabled(true);
    connect(link, &Link::linkClicked, [](const QString& link) {
        qDebug() << "linkClicked" << link;
    });

    Link* link2 = new Link("成功链接", "https://www.baidu.com", Link::Success, this);

    hLayout->addWidget(link);
    hLayout->addWidget(link2);

    // Input 输入框
    QHBoxLayout* hLayout2 = new QHBoxLayout();
    vLayout->addLayout(hLayout2);
    Input* input = new Input(Input::Clearable, this);
    Input* input2 = new Input(Input::ShowPassword, this);
    Input* input3 = new Input(Input::Calendar, this);
    hLayout2->addWidget(input);
    hLayout2->addWidget(input2);
    hLayout2->addWidget(input3);

    // Button 按钮
    QHBoxLayout* hLayout3 = new QHBoxLayout();
    vLayout->addLayout(hLayout3);
    Button* btn = new Button("默认按钮");
    Button* btn2 = new Button("主要按钮", Button::BT_Primary);
    Button* btn3 = new Button("成功按钮", Button::BT_Success);
    Button* btn4 = new Button("警告按钮", Button::BT_Warning);
    Button* btn5 = new Button("危险按钮", Button::BT_Danger);
    Button* btn6 = new Button("信息按钮", Button::BT_Info);

    hLayout3->addWidget(btn);
    hLayout3->addWidget(btn2);
    hLayout3->addWidget(btn3);
    hLayout3->addWidget(btn4);
    hLayout3->addWidget(btn5);
    hLayout3->addWidget(btn6);

    // 圆角 按钮
    QHBoxLayout* hLayout4 = new QHBoxLayout();
    vLayout->addLayout(hLayout4);
    Button* rbtn2 = new Button("主要按钮", Button::BT_Primary, Button::BS_Round);
    Button* rbtn3 = new Button("成功按钮", Button::BT_Success, Button::BS_Round);
    Button* rbtn4 = new Button("警告按钮", Button::BT_Warning, Button::BS_Round);
    Button* rbtn5 = new Button("危险按钮", Button::BT_Danger, Button::BS_Round);
    Button* rbtn6 = new Button("信息按钮", Button::BT_Info, Button::BS_Round);

    hLayout4->addWidget(rbtn2);
    hLayout4->addWidget(rbtn3);
    hLayout4->addWidget(rbtn4);
    hLayout4->addWidget(rbtn5);
    hLayout4->addWidget(rbtn6);

    // ICON 按钮
    QHBoxLayout* hLayout5 = new QHBoxLayout();
    vLayout->addLayout(hLayout5);
    Button* ibtn = new Button(fa::fa_add, Button::BT_Default);
    Button* ibtn2 = new Button(fa::fa_add, Button::BT_Primary);
    Button* ibtn3 = new Button(fa::fa_bookmark, Button::BT_Success);
    Button* ibtn4 = new Button(fa::fa_camera, Button::BT_Warning);
    Button* ibtn5 = new Button(fa::fa_dashboard, Button::BT_Danger);
    Button* ibtn6 = new Button(fa::fa_edit, Button::BT_Info);
    Button* ibtn7 = new Button("搜索", fa::fa_search, Button::BT_Primary);

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
    Switch* switch1 = new Switch("开关");
    Switch* switch2 = new Switch("禁用开关");
    switch2->setDisabled(true);
    hLayout6->addWidget(switch1);
    hLayout6->addWidget(switch2);

    // Checkbox 多选框
    Checkbox* cbx1 = new Checkbox("备选项");
    Checkbox* cbx2 = new Checkbox("备选项", Checkbox::LP_Left);
    Radio* rdo1 = new Radio("单选项1");
    Radio* rdo2 = new Radio("单选项2");
    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(rdo1);
    group->addButton(rdo2);
    group->setExclusive(true);

    hLayout6->addWidget(cbx1);
    hLayout6->addWidget(cbx2);
    hLayout6->addWidget(rdo1);
    hLayout6->addWidget(rdo2);

    // Avatar 头像
    QHBoxLayout* hLayout7 = new QHBoxLayout();
    vLayout->addLayout(hLayout7);
    Avatar* avatar1 = new Avatar("姓");
    Avatar* avatar2 = new Avatar(QImage(":/avatar.png"));
    hLayout7->addWidget(avatar1);
    hLayout7->addWidget(avatar2);

    // MessageBox 弹框
    QHBoxLayout* hLayout8 = new QHBoxLayout();
    vLayout->addLayout(hLayout8);
    Button* btn7 = new Button("消息提示 Message Box", Button::BT_Default);
    connect(btn7, &Button::clicked, [this]() {
        int ret = MessageBox::alert(this, "标题名称", "这是一段内容", "确定");
        qDebug() << ret;
    });
    Button* btn8 = new Button("确认消息 Message Box", Button::BT_Default);
    connect(btn8, &Button::clicked, [this]() {
        int ret = MessageBox::confirm(this, "提示", "此操作将永久删除该文件, 是否继续?", "确定", "取消");
        qDebug() << ret;
    });
    Button* btn9 = new Button("错误消息 Message Box", Button::BT_Default);
    connect(btn9, &Button::clicked, [this]() {
        int ret = MessageBox::error(this, "错误", "文件不存在！\n请重新选择", "确定");
        qDebug() << ret;
    });
    hLayout8->addWidget(btn7);
    hLayout8->addWidget(btn8);
    hLayout8->addWidget(btn9);

    // Select 选择器
    QHBoxLayout* hLayout9 = new QHBoxLayout();
    vLayout->addLayout(hLayout9);
    Select* select1 = new Select();
    select1->addItems(QStringList() << "黄金糕"
                                    << "双皮奶"
                                    << "蚵仔煎"
                                    << "龙须面");
    hLayout9->addWidget(select1);

    QHBoxLayout* hLayout10 = new QHBoxLayout();
    vLayout->addLayout(hLayout10);
    InputNumber* inputNum1 = new InputNumber(0, 10);
    hLayout10->addWidget(inputNum1);

    QHBoxLayout* hLayout11 = new QHBoxLayout();
    vLayout->addLayout(hLayout11);
    Card* card1 = new Card(QIcon(":/avatar.png"), "卡片名称1", "列表内容 1");
    Card* card2 = new Card(QIcon(":/avatar.png"), "卡片名称2", "列表内容 1");
    card2->setEnabled(false);
    hLayout11->addWidget(card1);
    hLayout11->addWidget(card2);

    // 线形进度条
    QHBoxLayout* hLayout12 = new QHBoxLayout();
    vLayout->addLayout(hLayout12);
    LineProgress* lineProgress1 = new LineProgress();
    lineProgress1->setValue(50);
    LineProgress* lineProgress2 = new LineProgress();
    lineProgress2->setValue(70);
    lineProgress2->setStatus(LineProgress::Success);
    LineProgress* lineProgress3 = new LineProgress();
    lineProgress3->setValue(80);
    lineProgress3->setStatus(LineProgress::Warning);
    hLayout12->addWidget(lineProgress1);
    hLayout12->addWidget(lineProgress2);
    hLayout12->addWidget(lineProgress3);

    // 环形进度条
    QHBoxLayout* hLayout13 = new QHBoxLayout();
    vLayout->addLayout(hLayout13);
    CircleProgress* circleProgress1 = new CircleProgress();
    circleProgress1->setPercent(60);
    hLayout13->addWidget(circleProgress1);
    CircleProgress* circleProgress2 = new CircleProgress();
    circleProgress2->setPercent(80);
    circleProgress2->setStatus(CircleProgress::Exception);
    hLayout13->addWidget(circleProgress2);

    setLayout(vLayout);
}

Widget::~Widget()
{
    delete ui;
}
