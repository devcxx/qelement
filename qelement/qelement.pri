
CONFIG += fontAwesomeFree

include($$PWD/../QtAwesome/QtAwesome/QtAwesome.pri)

INCLUDEPATH += $$PWD/../FramelessWindow

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/el_avatar.h \
    $$PWD/el_awesome.h \
    $$PWD/el_button.h \
    $$PWD/el_card.h \
    $$PWD/el_checkbox.h \
    $$PWD/el_global.h \
    $$PWD/el_inputnumber.h \
    $$PWD/el_link.h \
    $$PWD/el_input.h \
    $$PWD/el_messagebox.h \
    $$PWD/el_radio.h \
    $$PWD/el_select.h \
    $$PWD/el_slider.h \
    $$PWD/el_style.h \
    $$PWD/el_switch.h \

SOURCES += \
    $$PWD/el_avatar.cpp \
    $$PWD/el_button.cpp \
    $$PWD/el_card.cpp \
    $$PWD/el_checkbox.cpp \
    $$PWD/el_inputnumber.cpp \
    $$PWD/el_link.cpp \
    $$PWD/el_input.cpp \
    $$PWD/el_messagebox.cpp \
    $$PWD/el_radio.cpp \
    $$PWD/el_select.cpp \
    $$PWD/el_slider.cpp \
    $$PWD/el_switch.cpp \

RESOURCES += \
    $$PWD/qelement.qrc
