#-------------------------------------------------
#
# Project created by QtCreator 2014-02-26T15:20:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = motion_detect
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
