#-------------------------------------------------
#
# Project created by QtCreator 2018-01-11T19:52:57
#
#-------------------------------------------------

QT       += core gui

TARGET = SE_Terminal
TEMPLATE = app


SOURCES += main.cpp\
        se_terminal.cpp \
    usarttest.cpp \
    keydel.cpp \
    messageserver.cpp \
    osdmanager.cpp

HEADERS  += se_terminal.h \
    usarttest.h \
    keydel.h \
    messageserver.h \
    qtinterface.h \
    osdmanager.h

FORMS    += se_terminal.ui
