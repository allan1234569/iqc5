#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T11:43:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_sn695
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/radio_immunity/SN695

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_sn695.cpp

HEADERS  += w_sn695.h
