
CONFIG += fontAwesomeFree

include(QtAwesome/QtAwesome.pri)

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/el_global.h \
    $$PWD/el_link.h \
    $$PWD/el_input.h \
    $$PWD/el_style.h

SOURCES += \
    $$PWD/el_link.cpp \
    $$PWD/el_input.cpp \
