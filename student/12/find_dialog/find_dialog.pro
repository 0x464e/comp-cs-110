
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = colorpicker
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        find_dialog.cpp

HEADERS += \
        find_dialog.hh

FORMS += \
        find_dialog.ui