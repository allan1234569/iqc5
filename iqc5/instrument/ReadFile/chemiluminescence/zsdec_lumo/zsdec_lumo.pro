#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:33:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_lumo
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/LUMO

include($$PWD/../../../ReadFile/ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_lumo.cpp

HEADERS  += w_lumo.h
