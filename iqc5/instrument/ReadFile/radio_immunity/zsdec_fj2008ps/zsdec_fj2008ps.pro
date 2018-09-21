#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T16:46:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_fj2008ps
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/radio_immunity/FJ2008PS

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_fj2008ps.cpp

HEADERS  += w_fj2008ps.h
