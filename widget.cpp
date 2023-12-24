#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include "el_link.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QHBoxLayout *layout  =new QHBoxLayout();
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
    layout->addWidget(link);
    layout->addWidget(link2);
    setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
