
CONFIG += fontAwesomeFree

include(QtAwesome/QtAwesome/QtAwesome.pri)

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/el_avatar.h \
    $$PWD/el_awesome.h \
    $$PWD/el_button.h \
    $$PWD/el_global.h \
    $$PWD/el_link.h \
    $$PWD/el_input.h \
    $$PWD/el_style.h \
    $$PWD/el_switch.h \

SOURCES += \
    $$PWD/el_avatar.cpp \
    $$PWD/el_button.cpp \
    $$PWD/el_link.cpp \
    $$PWD/el_input.cpp \
    $$PWD/el_switch.cpp \
