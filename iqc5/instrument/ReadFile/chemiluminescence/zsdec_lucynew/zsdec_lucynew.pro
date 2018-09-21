#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:32:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_lucynew
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/LUCYNEW

include($$PWD/../../../ReadFile/ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_lucynew.cpp

HEADERS  += w_lucynew.h
