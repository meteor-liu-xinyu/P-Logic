#-------------------------------------------------
#
# Project created by QtCreator 2025-05-10T21:30:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = propositional-logic
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    calculate.cpp \
    calkanuo.cpp \
    helpinfomation.cpp \
    keybordshortcut.cpp \
    kmap.cpp \
    maketruthtable.cpp \
    modechoose.cpp \
    operation.cpp \
    paradigms.cpp \
    symbol.cpp \
    tableinput.cpp

HEADERS  += mainwidget.h \
    calculate.h \
    calkanuo.h \
    helpinfomation.h \
    keybordshortcut.h \
    kmap.h \
    maketruthtable.h \
    modechoose.h \
    operation.h \
    paradigms.h \
    symbol.h \
    tableinput.h

FORMS    += mainwidget.ui \
    helpinfomation.ui \
    keybordshortcut.ui \
    kmap.ui \
    maketruthtable.ui \
    modechoose.ui \
    symbol.ui \
    tableinput.ui

DISTFILES += \
    pl.ico

win32: RC_ICONS = pl.ico

