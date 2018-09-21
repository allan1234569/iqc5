#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T11:56:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 5195R
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/FlowCytometry/5195-R

include($$PWD/../../../ReadFile/ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_5195r.cpp

HEADERS  += w_5195r.h
