#-------------------------------------------------
#
# Project created by QtCreator 2015-07-04T10:43:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bucci-Source
TEMPLATE = app


SOURCES += main.cpp\
        buccimain.cpp \
    buccigame.cpp \
    card.cpp \
    player.cpp \
    deck.cpp \
    settings.cpp \
    stats.cpp

HEADERS  += buccimain.h \
    buccigame.h \
    card.h \
    player.h \
    deck.h \
    settings.h \
    stats.h

FORMS    += buccimain.ui \
    settings.ui \
    stats.ui
