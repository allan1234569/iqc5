QT += sql network

SOURCES += \
	$$PWD/basewindow.cpp \
	$$PWD/common.cpp \
	$$PWD/aprocess.cpp \
	$$PWD/clientsocket.cpp \
	$$PWD/adecodebase.cpp \
	$$PWD/asetupdialog.cpp \
	$$PWD/aadvancesetupdialog.cpp \
	$$PWD/asql.cpp \
	$$PWD/single_application.cpp

HEADERS += \
	$$PWD/basewindow.h \
	$$PWD/common.h \
	$$PWD/aprocess.h \
	$$PWD/clientsocket.h \
	$$PWD/adecodebase.h \
	$$PWD/asetupdialog.h \
	$$PWD/aadvancesetupdialog.h \
	$$PWD/asql.h \
	$$PWD/single_application.h

FORMS += \
        $$PWD/basewindow.ui \
	$$PWD/asetupdialog.ui \
	$$PWD/aadvancesetupdialog.ui

DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

RESOURCES += \
    $$PWD/pics.qrc

RC_FILE += $$PWD/ApplicationApp.rc
