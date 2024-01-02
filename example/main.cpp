#include "widget.h"

#include "QtAwesome.h"
#include "el_awesome.h"
#include <QApplication>
#include <iostream>

int main(int argc, char* argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication a(argc, argv);

    qAwesome->initFontAwesome();

    Widget w;
    w.show();
    return a.exec();
}
