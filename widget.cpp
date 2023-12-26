#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include "el_link.h"
#include "el_input.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QVBoxLayout* vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout  =new QHBoxLayout();
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

    QHBoxLayout *hLayout2  =new QHBoxLayout();
    el::Input* input = new el::Input(el::Input::Clearable, this);
    el::Input* input2 = new el::Input(el::Input::ShowPassword, this);
    el::Input* input3 = new el::Input(el::Input::Calendar, this);

    hLayout->addWidget(link);
    hLayout->addWidget(link2);

    hLayout2->addWidget(input);
    hLayout2->addWidget(input2);
    hLayout2->addWidget(input3);

    vLayout->addLayout(hLayout);
    vLayout->addLayout(hLayout2);
    setLayout(vLayout);
}

Widget::~Widget()
{
    delete ui;
}
