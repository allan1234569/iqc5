#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T17:10:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_da7600
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/PCR/DA7600

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_da7600.cpp

HEADERS  += w_da7600.h
