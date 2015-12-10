QT += core
QT -= gui
QT += core sql

TARGET = ComputerScientists
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    scientist.cpp \
    interface.cpp \
    repository.cpp \
    scientist_service.cpp \
    computers.cpp \
    computer_service.cpp

HEADERS += \
    scientist.h \
    interface.h \
    constants.h \
    repository.h \
    scientist_service.h \
    computers.h \
    computer_service.h
