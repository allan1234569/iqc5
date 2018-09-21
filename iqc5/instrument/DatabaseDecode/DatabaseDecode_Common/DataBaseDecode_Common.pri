SOURCES += \
	$$PWD/basewindow.cpp \
	$$PWD/single_application.cpp \
	$$PWD/aadvancesetupdialog.cpp \
	$$PWD/adecodebase.cpp \
	$$PWD/aprocess.cpp \
	$$PWD/asetupdialog.cpp \
	$$PWD/asql.cpp \
	$$PWD/common.cpp \
	$$PWD/aaccessdb.cpp

HEADERS += \
	$$PWD/basewindow.h \
	$$PWD/single_application.h \
	$$PWD/aadvancesetupdialog.h \
	$$PWD/adecodebase.h \
	$$PWD/aprocess.h \
	$$PWD/asetupdialog.h \
	$$PWD/asql.h \
	$$PWD/common.h \
	$$PWD/aaccessdb.h

FORMS += \
	$$PWD/basewindow.ui \
	$$PWD/aadvancesetupdialog.ui \
	$$PWD/asetupdialog.ui

UI_DIR += $$PWD/

DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

RESOURCES += \
    $$PWD/pics.qrc

RC_FILE += $$PWD/ApplicationApp.rc

