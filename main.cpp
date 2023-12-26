#include "widget.h"

#include <QApplication>
#include <iostream>
#include "QtAwesome.h"

int main(int argc, char *argv[])
{
#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    QApplication a(argc, argv);

    fa::QtAwesome::instance().initFontAwesome();


    Widget w;
    w.show();
    return a.exec();
}
