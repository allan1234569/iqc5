#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:11:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_bhp9507
TEMPLATE = app


DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/BHP9507

include($$PWD/../../../ReadFile/ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_bhp9507.cpp

HEADERS  += w_bhp9507.h
