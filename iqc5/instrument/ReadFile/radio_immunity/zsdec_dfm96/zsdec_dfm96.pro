#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T12:13:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_dfm96
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/radio_immunity/DFM96

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_dfm96.cpp

HEADERS  += w_dfm96.h
