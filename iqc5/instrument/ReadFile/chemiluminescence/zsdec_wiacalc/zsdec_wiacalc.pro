#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:35:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_wiacalc
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/WIACALC

include($$PWD/../../../ReadFile/ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_wiacalc.cpp

HEADERS  += w_wiacalc.h
