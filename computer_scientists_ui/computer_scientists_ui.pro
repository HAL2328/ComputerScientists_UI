#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T11:35:23
#
#-------------------------------------------------

QT       += core gui
QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = computer_scientists_ui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    repository.cpp \
    scientist_service.cpp

HEADERS  += mainwindow.h \
    repository.h \
    scientist_service.h

FORMS    += mainwindow.ui
